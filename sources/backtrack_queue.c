/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack_queue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:28:33 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/12 16:18:32 by swilliam         ###   ########.fr       */
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

static int	is_visited(
t_heads *heads,
t_stack *stack,
char *link_name
)
{
	int		i;
	t_rooms	*temp_room;

	i = 0;
	temp_room = find_room(&heads->rooms_head, link_name);
	while (i < stack->top)
	{
		if (ft_strcmp(stack->data[i].name, temp_room->name) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void printCurrentPath(t_stack stack) {
    for (int i = 0; i < stack.top; i++) {
        //strcpy(paths[pathIndex][i], stack.data[i].name);
		ft_printf("%s->", stack.data[i].name);
    }
	ft_printf("\n");
    //pathIndex++;
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
char *current_name
)
{
	t_rooms	*temp_room;
	t_links	*temp_links;

	temp_room = find_room(&heads->rooms_head, current_name);
	temp_links = NULL;
	push(stack, temp_room);
	if (temp_room->end)
	{
		//create_new_path(heads, )
		printCurrentPath(*stack);
		return ;
	}
	temp_links = temp_room->links;
	while (temp_links)
	{
		if (!is_visited(heads, stack, temp_links->name))
		{
			ft_printf("from %s to %s\n", temp_room->name, temp_links->name);
			trace_path(heads, stack, temp_links->name);
		}
		temp_links = temp_links->next;
	}
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

t_paths	*backtrack_queue(t_heads *heads)
{
	t_paths	*result;
	t_rooms	*start_room;
	t_stack	stack;

	result = NULL;
	stack.top = 0;
	start_room = find_start_room(&heads->rooms_head);
	//create_new_path(heads, start_room);
	//push(dfs_stack, start_room);
	trace_path(heads, &stack, start_room->name);
		//create_new_path(heads, start_room);
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
