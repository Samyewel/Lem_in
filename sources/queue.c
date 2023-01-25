/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:22:13 by sam               #+#    #+#             */
/*   Updated: 2023/01/25 18:58:30 by sam              ###   ########.fr       */
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
		ft_printf_strerror("Memory allocation failure in init_queue.");
	new_queue->data = (int *)malloc(sizeof(int) * size + 1);
	if (!new_queue->data)
		ft_printf_strerror("Memory allocation failure in init_queue.");
	while (++i < size)
		new_queue->data[i] = -1;
	new_queue->head = 0;
	new_queue->tail = 0;
	return (new_queue);
}

int		is_empty(t_queue *queue)
{
	return (queue->head == queue->tail);
}

void	dequeue(t_queue *queue)
{
	int	i;

	if (is_empty(queue))
		ft_printf_strerror("Queue is full.");
	queue->head++;
	i = queue->head;
	while (i < queue->tail)
		queue->data[i] = queue->data[i + 1];
	queue->tail--;
}

void	enqueue(t_queue *queue, int size, int value)
{
	if (!queue)
		ft_printf_strerror("Queue is not initialised.");
	if (queue->tail >= size)
	{
		ft_printf_strerror("Queue is full.");
		return;
	}
	queue->data[queue->tail] = value;
	queue->tail++;
}
