/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:04:24 by swilliam          #+#    #+#             */
/*   Updated: 2022/12/20 17:29:44 by swilliam         ###   ########.fr       */
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

	ft_printf("Creating node: %s\n", room->name);
	new_node = (t_queue *)malloc(sizeof(t_queue));
	if (!new_node)
		ft_printf_strerror("Memory allocation failure in create_path_node");
	new_node->name = ft_strdup(room->name);
	new_node->start = room->start;
	new_node->end = room->end;
	new_node->visited = false;
	new_node->valid = true;
	new_node->flow = 0;
	new_node->depth = 0;
	new_node->next = NULL;
	new_node->previous = previous;
	return (new_node);
}

/*
** create_path:
** -
*/

static t_paths	*create_path(t_paths *path, int i, t_queue *path_start)
{
	ft_printf("Creating new path %d\n", i);
	path = (t_paths *)malloc(sizeof(t_paths));
	if (!path)
		ft_printf_strerror("Memory allocation failure in create_path_node");
	path->path_nb = i;
	path->path = *path_start;
	path->next = NULL;
	return (path);
}

/*
** create_new_path:
** -
*/

void	create_new_path(t_paths **paths, t_rooms *room)
{
	t_paths	*temp_paths;
	t_queue	*path_start;
	t_paths	*path;
	int		i;

	i = 0;
	path_start = create_path_node(room, NULL);
	temp_paths = *paths;
	path = NULL;
	if (temp_paths == NULL)
	{
		ft_printf("temp_paths == NULL\n");
		path = create_path(*paths, 0, path_start);
		*paths = path;
		temp_paths = *paths;
		ft_printf("test: %d\n", temp_paths->path_nb);
	}
	else
	{
		ft_printf("temp_paths != NULL\n");
		while (temp_paths)
		{
			temp_paths = temp_paths->next;
			i++;
		}
		path = create_path(*paths, i, path_start);
		temp_paths->next = path;
	}
}

/*
** add_to_path:
** -
*/

void	add_to_path(t_paths **paths, t_rooms *room)
{
	t_paths	*temp_paths;
	t_queue	*temp_queue;

	temp_paths = *paths;
	temp_queue = NULL;
	ft_printf("Adding to paths...\n");
	//ft_printf("path nb = %d\n", temp_paths->path_nb);
	while (temp_paths)
	{
		temp_queue = &temp_paths->path;
		while (temp_queue)
		{
			if (temp_queue->next == NULL && temp_queue->end == false)
			{
				ft_printf("Adding to path[%d]: %s\n", temp_paths->path_nb, room->name);
				temp_queue->next = create_path_node(room, temp_queue);
				return ;
			}
			temp_queue = temp_queue->next;
		}
		temp_paths = temp_paths->next;
	}
	return ;
}
