/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack_queue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:28:33 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/13 15:47:48 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** is_visited
** - Cross-references the boolean array with the room ID to check
**   if that room has been visited yet.
*/

static bool	is_visited(t_heads *heads, bool *visited, char *link_name)
{
	t_rooms	*temp_room;

	temp_room = find_room(&heads->rooms_head, link_name);
	return (visited[temp_room->id]);
}

/*
** store_stack_reverse:
** - Since the rooms stored in the stack are in reverse order, we can
**   recursively traverse the list, storing them in reverse, therefore
**   they are sorted in regular order.
*/

static void	store_stack_reverse(t_heads *heads, t_node *current)
{
	if (!current)
		return ;
	store_stack_reverse(heads, current->next);
	if (current->start)
		create_new_path(heads, current);
	else
		store_path_data(heads, current);
}

/*
** trace_path:
** - Recursively checks all valid rooms to find a path from start to end.
** - Pushes the current room to the stack for path storage purposes.
** - Sets the current room as visited in the boolean array for validation
**   purposes further down the exploration path.
** - When the end room is found, a linked-list is created using all the
**   nodes still stored in the stack.
*/

static void	trace_path(
t_heads *heads,
t_stack *stack,
bool *visited,
char *current_name)
{
	t_rooms			*temp_room;
	t_links			*temp_links;

	temp_room = find_room(&heads->rooms_head, current_name);
	push(stack, temp_room);
	visited[temp_room->id] = true;
	temp_links = NULL;
	if (temp_room->end)
		store_stack_reverse(heads, stack->nodes);
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

/*
** backtrack_queue:
** - Creates a boolean array to check each which rooms have been visited.
** - Creates a stack with the value "top". This stack stores rooms that are
**	 visited to later see the path made to reach the end room.
** - calls trace_path, which recursively explores each path to find every
**	 possible path from the start room to the end room.
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
