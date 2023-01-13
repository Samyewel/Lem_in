/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:30:16 by sam               #+#    #+#             */
/*   Updated: 2023/01/13 15:21:46 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** clean_queue:
** - Flushes the contents of the queue.
*/

void	clean_queue(t_queue **queue)
{
	t_queue	*temp_queue;
	t_queue	*temp_data;

	temp_queue = *queue;
	while (temp_queue)
	{
		temp_data = temp_queue->next;
		ft_strdel(&temp_queue->name);
		free(temp_queue);
		temp_queue = temp_data;
	}
}

void	clean_paths(t_heads *heads)
{
	t_paths	*temp_paths;
	t_queue	*temp_queue;
	t_paths	*temp_data;

	temp_paths = heads->paths_head;
	while (temp_paths)
	{
		temp_queue = &temp_paths->path;
		clean_queue(&temp_queue);
		temp_data = temp_paths->next;
		free(temp_paths);
		temp_paths = temp_data;
	}
}
