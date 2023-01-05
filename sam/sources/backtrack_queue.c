/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack_queue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:28:33 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/05 16:12:08 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** is_valid:
** - Checks that the room being checked is meets the criteria to allow
**   the backtrack algorithm to continue.
** - A room is valid if:
**   - It has more than one link.
**   - It is not coming from the start room.
**   - It is not returning to the parent.
*/

// !start, !1, !6, !8, !2, !12, !7, !9, !3, !4, !10, !end, !11, !5
// #        12     4 - 5
// #         |    /     \
// # start - 1 - 2 - 3 - end
// #    | \     /    |
// #    |  6 - 7     |
// #    |            |
// #    8 - 9 - 10 - 11
// PATH [1] = start -> 1 -> 2 -> 4 -> 5 -> end
// PATH [2] = start -> 8 -> 9 -> 10 -> 11 -> 3 -> end

static int	is_valid(
t_queue **queue,
t_rooms *parent,
t_rooms *current,
char *link_name)
{
	t_queue	*temp_queue;

	temp_queue = *queue;

	if (parent->end \
		|| ft_strcmp(parent->name, link_name) == 0)
		return (0);
	while (temp_queue)
	{
		if (ft_strcmp(temp_queue->name, current->name) == 0 \
			&& temp_queue->valid && temp_queue->visited == false)
			{
				temp_queue->visited = true;
				return (1);
			}
		temp_queue = temp_queue->next;
	}
	return (0);
}

/*
** trace_path:
** - Recursively checks all valid rooms to find a path from end to start.
** - Once start is found, a linked-list is created with that node, and
**   returns true back up the recursion path, adding each node into the list.
*/

// !start, !1, !6, !8, !2, !12, !7, !9, !3, !4, !10, !end, !11, !5
// #        12     4 - 5
// #         |    /     \
// # start - 1 - 2 - 3 - end
// #    | \     /    |
// #    |  6 - 7     |
// #    |            |
// #    8 - 9 - 10 - 11
// PATH [1] = start -> 1 -> 2 -> 4 -> 5 -> end
// PATH [2] = start -> 8 -> 9 -> 10 -> 11 -> 3 -> end

static int	trace_path(
t_heads *heads,
t_rooms *parent,
char *link
)
{
	t_rooms	*temp_room;
	t_links	*temp_links;

	temp_room = NULL;
	temp_links = NULL;
	temp_room = find_room(&heads->rooms_head, link);
	if (!is_valid(&heads->queue_head, parent, temp_room, link))
		return (0);
	if (temp_room->end)
	{
		reset_visted(&heads->queue_head);
		create_new_path(heads, temp_room);
		return (1);
	}
	temp_links = temp_room->links;
	while (temp_links)
	{
		if (trace_path(heads, temp_room, temp_links->name))
		{
			store_path_data(heads, temp_room);
			return (1);
		}
		temp_links = temp_links->next;
	}
	return (0);
}

// !start, !1, !6, !8, !2, !12, !7, !9, !3, !4, !10, !end, !11, !5
// #        12     4 - 5
// #         |    /     \
// # start - 1 - 2 - 3 - end
// #    | \     /    |
// #    |  6 - 7     |
// #    |            |
// #    8 - 9 - 10 - 11
// PATH [1] = start -> 1 -> 2 -> 4 -> 5 -> end
// PATH [2] = start -> 8 -> 9 -> 10 -> 11 -> 3 -> end

/*
** backtrack_queue:
** - Searches each link from the end node, recursively tracing each link
**   for any paths leading to the start node, storing them in a linked-list.
*/

t_paths	*backtrack_queue(t_heads *heads)
{
	t_paths				*result;
	t_rooms				*start_room;
	t_links				*temp_links;

	result = NULL;
	start_room = find_start_room(&heads->rooms_head);
	temp_links = start_room->links;
	while (temp_links)
	{
		if (trace_path(heads, start_room, temp_links->name))
			store_path_data(heads, start_room);
		temp_links = temp_links->next;
	}
	if (DEBUG == true && PATHS == true)
		print_paths(&heads->paths_head);
	return (result);
}

/*
create graph to store all possible outputs:
start->1->2->4->5->end
start->1->2->3->end
start->6->7->2->4->5->end
start->6->7->2->3->end
start->8->9->10->11->3->end
start->8->9->10->11->3->2->4->5->end
*/
