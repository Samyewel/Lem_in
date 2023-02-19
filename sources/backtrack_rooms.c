/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack_rooms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:28:33 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/16 13:47:53 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// /*
// ** is_visited
// ** - Cross-references the boolean array with the room ID to check
// **   if that room has been visited yet.
// */

// static bool	is_visited(bool *visited, t_rooms *room)
// {
// 	return (visited[room->id]);
// }

/*
** store_stack_reverse:
** - Since the rooms stored in the stack are in reverse order, we can
**   recursively traverse the list, storing them in reverse, therefore
**   they are sorted in regular order.
*/

static void	store_stack_reverse(t_heads *heads, t_node *current)
{
	if (current->next)
		store_stack_reverse(heads, current->next);
	if (heads->room[current->id]->start)
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
** - When the end room is found, an array is created using all the
**   nodes still stored in the stack.
*/

static void	trace_path(
t_heads *heads,
bool *visited,
int current)
{
	int	i;

	i = -1;
	push(heads->stack, heads->room[current], heads);
	visited[current] = true;
	ft_printf("                 \r");
	ft_printf("\r[%d] Tracing %s", heads->stack->top, heads->room[current]->name);
	if (heads->room[current]->end && heads->stack->top <= MAX_DEPTH)
	{
		store_stack_reverse(heads, heads->stack->nodes);
		ft_printf("                 \r");
		ft_printf("Path count = %d\n", heads->data->path_count);
	}
	else if (!heads->room[current]->end && heads->stack->top < MAX_DEPTH)
	{
		while (++i < MAX_SIZE && heads->room[current]->links[i] != NULL)
		{
			if (!visited[heads->room[current]->links[i]->id])
				trace_path(heads, visited, heads->room[current]->links[i]->id);
		}
	}
	if (heads->stack->top < MAX_DEPTH)
		visited[current] = false;
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

void	backtrack_rooms(t_data *data, t_heads *heads)
{
	int		start_room;
	bool	*visited;

	start_room = find_start_room(heads);
	visited = (bool *) malloc(sizeof(bool) * data->room_count);
	if (!visited)
		clean_lem_in(heads, "Memory allocation failure in backtrack_queue.");
	heads->stack = (t_stack *)malloc(sizeof(t_stack));
	heads->stack->top = 0;
	trace_path(heads, visited, start_room);
	free(visited);
	if (heads->path == NULL)
		clean_lem_in(heads, "No paths found.");
}
