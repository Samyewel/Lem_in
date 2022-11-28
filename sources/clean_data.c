/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:30:16 by sam               #+#    #+#             */
/*   Updated: 2022/11/28 21:28:30 by sam              ###   ########.fr       */
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
		//temp_queue->name = NULL;
		ft_strdel(&temp_queue->name);
		temp_data = temp_queue->next;
		free(temp_queue);
		temp_queue = temp_data;
	}
}
