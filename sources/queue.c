/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:22:53 by sam               #+#    #+#             */
/*   Updated: 2022/11/28 16:59:09 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue	*create_queue_node(t_queue *queue, char *room_name)
{
	queue = (t_queue *)malloc(sizeof(t_queue));
	if (!queue)
		ft_printf_strerror("Memory allocation failure in \
		initialise_queue_node");
	queue->name = NULL;
	queue->name = ft_strdup(room_name);
	queue->next = NULL;
	queue->visited = false;
	return (queue);
}

// t_queue	*add_to_queue(t_queue *queue, char *room_name)
// {
// 	queue->name = ft_strdup(room_name);
// 	return(queue)
// }

int		is_empty(t_queue **queue)
{
	t_queue	*temp;

	temp = *queue;
	while (temp)
	{
		if (temp->visited == false)
			return (0);
		temp = temp->next;
	}
	return (1);
}

t_rooms	*visit_next(t_queue **queue, t_rooms **rooms)
{
	t_queue	*temp_queue;

	temp_queue = *queue;
	while (temp_queue)
	{
		if (temp_queue->visited == false)
			return (find_room(rooms, temp_queue->name));
		temp_queue = temp_queue->next;
	}
	return (NULL);
}