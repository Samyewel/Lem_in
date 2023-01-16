/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:09:45 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/16 21:56:30 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** create_path_node:
** -
*/

static t_queue	*create_path_node(t_rooms *room, t_queue *previous)
{
	t_queue	*new_node;

	new_node = (t_queue *)malloc(sizeof(t_queue));
	if (!new_node)
		ft_printf_strerror("Memory allocation failure in create_path_node");
	new_node->name = ft_strdup(room->name);
	new_node->start = room->start;
	new_node->end = room->end;
	new_node->visited = false;
	new_node->valid = true;
	new_node->flow = 0 + (room->start == false && room->end == false);
	new_node->depth = 0;
	new_node->next = NULL;
	new_node->previous = previous;
	return (new_node);
}

/*
** create_path:
** - Allocates a fresh
*/

static t_paths	*create_path(int i, t_queue *path_start)
{
	t_paths	*new_path;

	new_path = NULL;
	new_path = (t_paths *)malloc(sizeof(t_paths));
	if (!new_path)
		ft_printf_strerror("Memory allocation failure in create_path_node");
	new_path->path_nb = i;
	new_path->path = path_start;
	new_path->flow = 0;
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
	t_queue	*path_start;
	t_paths	*path;
	int		i;

	i = 0;
	start_room = find_room(&heads->rooms_head, start_node->name);
	path = NULL;
	path_start = create_path_node(start_room, NULL);
	temp_paths = heads->paths_head;
	if (heads->paths_head == NULL)
	{
		path = create_path(0, path_start);
		heads->paths_head = path;
		temp_paths = heads->paths_head;
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
	t_paths	*temp_paths;
	t_queue	*temp_queue;
	t_rooms	*temp_room;

	temp_room = find_room(&heads->rooms_head, node->name);
	temp_paths = heads->paths_head;
	temp_queue = NULL;
	while (temp_paths)
	{
		temp_queue = temp_paths->path;
		while (temp_queue)
		{
			if (temp_queue->next == NULL && temp_queue->end == false)
			{
				temp_queue->next = create_path_node(temp_room, temp_queue);
				return ;
			}
			temp_queue = temp_queue->next;
		}
		temp_paths = temp_paths->next;
	}
	return ;
}
