/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:09:45 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/28 14:03:45 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** create_path_node:
** -
*/

static t_rooms	*create_path_node(t_rooms *room, t_rooms *previous)
{
	t_rooms	*new_node;

	new_node = (t_rooms *)malloc(sizeof(t_rooms));
	if (!new_node)
		ft_printf_strerror("Memory allocation failure in create_path_node");
	new_node->name = ft_strdup(room->name);
	new_node->start = room->start;
	new_node->end = room->end;
	new_node->is_room = 0 + (room->start == false && room->end == false);
	new_node->visited = false;
	new_node->index = 0;
	new_node->next = NULL;
	new_node->previous = previous;
	return (new_node);
}

/*
** create_path:
** - Allocates a fresh
*/

static t_paths	*create_path(int i, t_rooms *path_start)
{
	t_paths	*new_path;

	new_path = NULL;
	new_path = (t_paths *)malloc(sizeof(t_paths));
	if (!new_path)
		ft_printf_strerror("Memory allocation failure in create_path_node");
	new_path->nb = i;
	new_path->path = path_start;
	new_path->length = 0;
	new_path->usage_times = 0;
	new_path->temp = 0;
	new_path->next = NULL;
	return (new_path);
}

/*
** create_new_path:
** -
*/

void	create_new_path(t_heads *heads, t_node *start_node)
{
	t_rooms	*start_room;
	t_paths	*temp_paths;
	t_rooms	*path_start;
	t_paths	*path;
	int		i;

	i = 0;
	start_room = find_room(&heads->rooms, start_node->name);
	path = NULL;
	path_start = create_path_node(start_room, NULL);
	temp_paths = heads->paths;
	if (heads->paths == NULL)
	{
		path = create_path(0, path_start);
		heads->paths = path;
		temp_paths = heads->paths;
	}
	else
	{
		while (++i && temp_paths->next != NULL)
			temp_paths = temp_paths->next;
		path = create_path(i, path_start);
		temp_paths->next = path;
		temp_paths = temp_paths->next;
	}
}

/*
** add_to_path:
** -
*/

void	store_path_data(t_heads *heads, t_node *node)
{
	t_paths	*temp_path;
	t_rooms	*temp_node;
	t_rooms	*temp_room;

	temp_room = find_room(&heads->rooms, node->name);
	temp_path = heads->paths;
	temp_node = NULL;
	while (temp_path)
	{
		temp_node = temp_path->path;
		while (temp_node)
		{
			if (temp_node->next == NULL && temp_node->end == false)
			{
				temp_node->next = create_path_node(temp_room, temp_node);
				temp_path->length++;
				return ;
			}
			temp_node = temp_node->next;
		}
		temp_path = temp_path->next;
	}
	return ;
}
