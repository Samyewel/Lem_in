/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack_rooms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:28:33 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/27 15:22:21 by sam              ###   ########.fr       */
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

	temp_room = find_room(&heads->rooms, link_name);
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
bool *visited,
char *current_name)
{
	t_rooms	*temp_room;
	t_links	*temp_links;

	temp_room = find_room(&heads->rooms, current_name);
	push(heads->stack, temp_room);
	visited[temp_room->id] = true;
	temp_links = NULL;
	if (temp_room->end)
		store_stack_reverse(heads, heads->stack->nodes);
	else
	{
		temp_links = temp_room->links;
		while (temp_links)
		{
			if (!is_visited(heads, visited, temp_links->name))
				trace_path(heads, visited, temp_links->name);
			temp_links = temp_links->next;
		}
	}
	visited[temp_room->id] = false;
	pop(heads->stack);
}

/*
** backtrack_queue:
** - Creates a boolean array to check each which rooms have been visited.
** - Creates a stack with the value "top". This stack stores rooms that are
**	 visited to later see the path made to reach the end room.
** - calls trace_path, which recursively explores each path to find every
**	 possible path from the start room to the end room.
*/

void	backtrack_rooms(t_heads *heads, t_data *data)
{
	t_rooms	*start_room;
	bool	*visited;

	start_room = find_start_room(&heads->rooms);
	visited = (bool *) malloc(sizeof(bool) * data->room_count);
	if (!visited)
		ft_printf_strerror("Memory allocation failure in backtrack_queue");
	heads->stack = (t_stack *)malloc(sizeof(t_stack));
	heads->stack->top = 0;
	ft_memset(visited, false, data->room_count);
	trace_path(heads, visited, start_room->name);
	free(visited);
	if (heads->paths == NULL)
		ft_printf_strerror("No paths found.");
	print_paths(&heads->paths);
}
