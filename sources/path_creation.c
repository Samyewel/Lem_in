/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:09:45 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/10 12:40:38 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** create_path_node:
** - Duplicates the room with necessary data to be used when accessing the
**   path later.
*/

static t_rooms	*create_path_node(t_rooms *room, t_rooms *prev, t_heads *heads)
{
	t_rooms	*new_node;

	new_node = (t_rooms *)malloc(sizeof(t_rooms));
	if (!new_node)
		clean_lem_in(heads, "Memory allocation failure in create_path_node");
	new_node->id = room->id;
	new_node->name = ft_strdup(room->name);
	new_node->start = room->start;
	new_node->end = room->end;
	new_node->is_room = (room->start == false && room->end == false);
	new_node->visited = false;
	new_node->ants = 0;
	new_node->next = NULL;
	new_node->previous = prev;
	return (new_node);
}

/*
** create_path:
** - Allocates a fresh array with the start path at the beginning.
*/

static t_paths	*create_path(
t_heads *heads,
int i,
t_rooms *path_start)
{
	t_paths	*new_path;

	new_path = NULL;
	new_path = (t_paths *)malloc(sizeof(t_paths));
	if (!new_path)
		clean_lem_in(heads, "Memory allocation failure in create_path_node.");
	new_path->nb = i;
	new_path->room = (t_rooms **)malloc(sizeof(t_rooms *) * MAX_SIZE);
	if (!new_path->room)
		clean_lem_in(heads, "Memory allocation failure in create_path_node.");
	ft_memset(new_path->room, 0, MAX_SIZE);
	new_path->room[0] = path_start;
	new_path->length = 0;
	new_path->usage = 0;
	new_path->temp = 0;
	new_path->next = NULL;
	heads->data->path_count++;
	return (new_path);
}

/*
** create_new_path:
** - Creates a fresh path containing the start node at the beginning, storing
**   it at the end of the list of paths.
*/

void	create_new_path(t_heads *heads, t_node *start_node)
{
	t_rooms	*start_room;
	t_paths	*temp_paths;
	t_rooms	*path_start;
	int		i;

	i = 0;
	start_room = find_room(heads->room, start_node->id);
	path_start = create_path_node(start_room, NULL, heads);
	temp_paths = heads->path_list;
	if (heads->path_list == NULL)
	{
		heads->path_list = create_path(heads, 0, path_start);
		if (!heads->path_list)
			clean_lem_in(heads, "Memory allocation failure in create_new_path");
	}
	else
	{
		while (++i && temp_paths->next != NULL)
			temp_paths = temp_paths->next;
		temp_paths->next = create_path(heads, i, path_start);
		if (!temp_paths->next)
			clean_lem_in(heads, "Memory allocation failure in create_new_path");
	}
}

/*
** add_to_path:
** - Loops through the paths until it finds an unfinished one, adding the
**   room onto the end of it.
*/

void	store_path_data(t_heads *heads, t_node *node)
{
	t_paths	*temp_path;
	int		i;

	i = -1;
	temp_path = heads->path_list;
	while (temp_path)
	{
		i = -1;
		while (++i < MAX_SIZE)
		{
			if (temp_path->room[i + 1] == NULL)
			{
				if (temp_path->room[i]->end == false)
				{
					temp_path->room[i + 1] = create_path_node \
						(heads->room[node->id], temp_path->room[i], heads);
					temp_path->length++;
					return ;
				}
				else
					temp_path = temp_path->next;
				break ;
			}
		}
	}
}
