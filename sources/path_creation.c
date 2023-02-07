/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:09:45 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/06 15:52:56 by sam              ###   ########.fr       */
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

	ft_printf("Adding %s.\n", room->name);
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
	ft_printf("Added.\n");
	return (new_node);
}

/*
** create_path:
** - Allocates a fresh
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
		ft_printf_strerror("Memory allocation failure in create_path_node");
	new_path->nb = i;
	new_path->path = (t_rooms **)malloc(sizeof(t_rooms *) * MAX_SIZE);
	if (!new_path->path)
		ft_printf_strerror("Memory allocation failure in create_path_node");
	ft_memset(new_path->path, 0, MAX_SIZE);
	new_path->path[0] = path_start;
	new_path->length = 0;
	new_path->usage_times = 0;
	new_path->temp = 0;
	new_path->next = NULL;
	heads->data->path_count++;
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
	ft_printf("start_node->id = %d\n", start_node->id);
	start_room = find_room(heads->room_array, start_node->id);
	ft_printf("Start room = %s\n", start_room->name);
	path = NULL;
	path_start = create_path_node(start_room, NULL);
	temp_paths = heads->paths;
	if (heads->paths == NULL)
	{
		path = create_path(heads, 0, path_start);
		heads->paths = path;
		temp_paths = heads->paths;
	}
	else
	{
		while (++i && temp_paths->next != NULL)
			temp_paths = temp_paths->next;
		path = create_path(heads, i, path_start);
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
	int		i;

	ft_printf("Storing %s\n", heads->room_array[node->id]->name);
	i = -1;
	temp_path = heads->paths;
	while (temp_path)
	{
		ft_printf("Path %d:\n", temp_path->nb);
		i = -1;
		while (++i < MAX_SIZE)
		{
			ft_printf("[%d] %s\n", i, temp_path->path[i]->name);
			if (temp_path->path[i]->end == false && temp_path->path[i + 1] == NULL)
			{
				temp_path->path[i + 1] = create_path_node(heads->room_array[node->id], temp_path->path[i]);
				temp_path->length++;
				ft_printf("Stored\n");
				return ;
			}
		}
		temp_path = temp_path->next;
	}
	return ;
}
