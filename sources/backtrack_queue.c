/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack_queue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:28:33 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/12 20:20:01 by swilliam         ###   ########.fr       */
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

static bool	is_visited(
t_heads *heads,
bool *visited,
char *link_name
)
{
	t_rooms	*temp_room;

	temp_room = find_room(&heads->rooms_head, link_name);
	return (visited[temp_room->id]);
}

static void printCurrentPath(t_stack stack)
{
	int	i;

	i = 0;
    while (i < stack.top)
	{
		ft_printf("%s->", stack.nodes[i].name);
		i++;
    }
	ft_printf("\n");
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

static void	trace_path(
t_heads *heads,
t_stack *stack,
bool *visited,
char *current_name
)
{
	t_rooms	*temp_room;
	t_links	*temp_links;

	temp_room = find_room(&heads->rooms_head, current_name);
	push(stack, temp_room);
	visited[temp_room->id] = true;
	temp_links = NULL;
	if (temp_room->end)
	{
		printCurrentPath(*stack);
	}
	else
	{
		temp_links = temp_room->links;
		while (temp_links)
		{
			if (!is_visited(heads, visited, temp_links->name))
				trace_path(heads, stack, visited, temp_links->name);

			temp_links = temp_links->next;
		}
	}
	visited[temp_room->id] = false;
	pop(stack);
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

t_paths	*backtrack_queue(t_heads *heads, t_data *data)
{
	t_paths	*result;
	t_rooms	*start_room;
	t_stack	stack;
	bool	*visited;

	result = NULL;
	visited = (bool *) malloc(sizeof(bool) * data->room_count);
	if (!visited)
		ft_printf_strerror("Memory allocation failure in backtrack_queue");
	start_room = find_start_room(&heads->rooms_head);
	stack.top = 0;
	ft_memset(visited, false, data->room_count);
	trace_path(heads, &stack, visited, start_room->name);
	if (DEBUG == true && PATHS == true)
		print_paths(&heads->paths_head);
	free(visited);
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
