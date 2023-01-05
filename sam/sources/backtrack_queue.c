/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack_queue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:28:33 by swilliam          #+#    #+#             */
/*   Updated: 2022/12/21 17:23:21 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** find_depth:
** - Searches for depth given to each node during the BFS to be used to
**   ensure a path is heading towards start.
*/

static int	find_depth(t_queue **queue, char *room_name)
{
	t_queue	*temp_queue;

	temp_queue = *queue;
	while (temp_queue)
	{
		if (ft_strcmp(temp_queue->name, room_name) == 0)
			return (temp_queue->depth);
		temp_queue = temp_queue->next;
	}
	return (-1);
}

/*
** is_valid:
** - Checks that the room being checked is meets the criteria to allow
**   the backtrack algorithm to continue.
** - A room is valid if:
**   - It has more than one link.
**   - It is not coming from the start room.
**   - It is not returning to the parent.
*/

static int	is_valid(
t_queue **queue,
t_rooms *parent,
t_rooms *current,
char *link_name)
{
	t_queue	*temp_queue;

	temp_queue = NULL;
	temp_queue = *queue;
	if (parent->start || current->end \
		|| ft_strcmp(parent->name, link_name) == 0)
		return (0);
	while (temp_queue)
	{
		if (ft_strcmp(temp_queue->name, current->name) == 0 \
			&& find_depth(queue, current->name) >= find_depth(queue, link_name))
			return (temp_queue->valid);
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
	if (temp_room->start)
	{
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
	t_rooms				*end_room;
	t_links				*temp_links;

	result = NULL;
	end_room = find_end_room(&heads->rooms_head);
	temp_links = end_room->links;
	while (temp_links)
	{
		if (trace_path(heads, end_room, temp_links->name))
			store_path_data(heads, end_room);
		temp_links = temp_links->next;
	}
	if (DEBUG == true && PATHS == true)
		print_paths(&heads->paths_head);
	return (result);
}
