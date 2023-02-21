/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:09:45 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/21 14:47:20 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** create_path_node:
** - Duplicates the room with necessary data to be used when accessing the
**   path later.
*/

static t_rooms	*create_path_node(t_rooms *room)
{
	t_rooms	*new_node;

	new_node = NULL;
	new_node = (t_rooms *)malloc(sizeof(t_rooms));
	if (!new_node)
		clean_lem_in("Memory allocation failure in create_path_node");
	new_node->id = room->id;
	new_node->name = ft_strdup(room->name);
	new_node->start = room->start;
	new_node->end = room->end;
	new_node->is_room = (room->start == false && room->end == false);
	new_node->visited = false;
	new_node->ants = 0;
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}

/*
** create_path:
** - Allocates a fresh path.
*/

static t_paths	*create_path(
t_heads *heads,
int i)
{
	t_paths	*new_path;

	new_path = NULL;
	new_path = (t_paths *)malloc(sizeof(t_paths));
	if (!new_path)
		clean_lem_in("Memory allocation failure in create_path_node.");
	new_path->nb = i;
	new_path->room = (t_rooms **)ft_memalloc(sizeof(t_rooms *) * MAX_SIZE);
	if (!new_path->room)
		clean_lem_in("Memory allocation failure in create_path_node.");
	new_path->room[0] = NULL;
	new_path->length = 0;
	new_path->usage = 0;
	new_path->temp_usage = 0;
	new_path->bfs_index = 0;
	new_path->temp = 0;
	new_path->next = NULL;
	heads->data->path_count++;
	return (new_path);
}

/*
** add_to_path_front:
** - Shifts all node one to the right, storing the new node at the beginning
**   of the list.
*/

static void	add_to_path_front(t_heads *heads, t_paths *path, t_rooms *room)
{
	int		i;
	t_rooms	*new_node;

	i = heads->data->room_count;
	new_node = NULL;
	while (--i >= 0)
	{
		if (path->room[i] != NULL)
			path->room[i + 1] = path->room[i];
	}
	new_node = create_path_node(room);
	path->room[0] = new_node;
	path->length++;
}

/*
** store_path_data:
** - Backtracks the parent array to find a path from the end to start, storing
**   it in reverse order so that it is from start to end.
*/

static void	store_path_data(t_heads *heads, t_paths *path, int end)
{
	int	node;

	node = end;
	while (node != -1)
	{
		add_to_path_front(heads, path, heads->room[node]);
		node = heads->parent[node];
	}
}

/*
** create_new_path:
** - Creates a fresh path and stores it at the end of the list of paths.
*/

void	create_new_path(t_heads *heads, int end)
{
	int	i;

	i = -1;
	if (heads->path == NULL)
	{
		heads->path = (t_paths **)ft_memalloc(sizeof(t_paths *) * MAX_SIZE);
		if (!heads->path)
			clean_lem_in("Memory allocation failure in create_new_path");
	}
	while (++i < heads->data->room_count)
	{
		if (heads->path[i] == NULL)
		{
			heads->path[i] = create_path(heads, i);
			store_path_data(heads, heads->path[i], end);
			break ;
		}
	}
}
