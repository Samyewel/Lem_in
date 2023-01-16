/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:30:16 by sam               #+#    #+#             */
/*   Updated: 2023/01/16 12:45:41 by sam              ###   ########.fr       */
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
	t_paths	*current_path;
	t_paths	*next_path;

	current_path = heads->paths_head;
	next_path = NULL;
	while (current_path != NULL)
	{
		next_path = current_path->next;
		clean_queue(&current_path->path);
		free(current_path);
		current_path = next_path;
	}
	heads->paths_head = NULL;
}
