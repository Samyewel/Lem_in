/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:03:20 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/17 11:31:10 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** create_queue_node:
** - Allocates a fresh link to be added to the queue, setting the name
**   as the room name given as a variable.
*/

t_queue	*create_queue(t_queue *queue, char *room_name, t_queue *prev, int depth)
{
	queue = (t_queue *)malloc(sizeof(t_queue));
	if (!queue)
		ft_printf_strerror("Memory allocation failure in create_queue_node");
	queue->name = NULL;
	queue->name = ft_strdup(room_name);
	if (!queue->name)
		ft_printf_strerror("Memory allocation failure in create_queue_node");
	queue->next = NULL;
	queue->previous = prev;
	queue->depth = depth;
	queue->start = false;
	queue->end = false;
	queue->visited = false;
	return (queue);
}
