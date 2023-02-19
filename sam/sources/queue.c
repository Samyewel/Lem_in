/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:10:03 by sam               #+#    #+#             */
/*   Updated: 2023/02/19 15:40:19 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue	*init_queue(int size)
{
	t_queue	*new_queue;
	int		i;

	i = -1;
	new_queue = NULL;
	new_queue = (t_queue *)malloc(sizeof(t_queue));
	if (!new_queue)
		clean_lem_in("Memory allocation failure in init_queue.");
	new_queue->data = (int *)malloc(sizeof(int) * size);
	if (!new_queue->data)
		clean_lem_in("Memory allocation failure in init_queue.");
	new_queue->size = size;
	while (++i < size)
		new_queue->data[i] = -1;
	new_queue->head = 0;
	new_queue->tail = 0;
	return (new_queue);
}

int	is_empty(t_queue *queue)
{
	return (queue->head >= queue->tail);
}

void	enqueue(t_queue *queue, int value)
{
	if (!queue)
		ft_printf_strerror("Queue is not initialised.");
	if (queue->tail < queue->size)
	{
		queue->data[queue->tail] = value;
		queue->tail++;
	}
	else
	{
		ft_printf_strerror("Queue is full.");
		return ;
	}
}

void	dequeue(t_queue *queue)
{
	if (is_empty(queue))
		return ;
	queue->head++;
}
