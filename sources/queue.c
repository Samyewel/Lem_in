/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:22:53 by sam               #+#    #+#             */
/*   Updated: 2022/12/08 16:50:15 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** create_queue_node:
** - Allocates a fresh link to be added to the queue, setting the name
**   as the room name given as a variable.
*/

t_queue	*create_queue_node(t_queue *queue, char *room_name)
{
	queue = (t_queue *)malloc(sizeof(t_queue));
	if (!queue)
		ft_printf_strerror("Memory allocation failure in create_queue_node");
	queue->name = NULL;
	queue->name = ft_strdup(room_name);
	if (!queue->name)
		ft_printf_strerror("Memory allocation failure in create_queue_node");
	queue->next = NULL;
	queue->previous = NULL;
	queue->start = false;
	queue->end = false;
	queue->visited = false;
	queue->valid = true;
	return (queue);
}

/*
** is_empty:
** - Scans the queue and checks whether every room has been visited.
*/

int	is_empty(t_queue **queue)
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

/*
** visit_next:
** - Points to the next room in the queue that has not been visited.
*/

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

/*
** is_duplicate:
** - Checks if the name of the link that is given as a variable is already
**   found within the queue.
*/

static int	is_dupe(t_queue **queue, char *link_name)
{
	t_queue	*temp_queue;

	temp_queue = *queue;
	while (temp_queue)
	{
		if (ft_strcmp(temp_queue->name, link_name) == 0)
			return (1);
		temp_queue = temp_queue->next;
	}
	return (0);
}

/*
** explore_room:
** - Takes a room as a variable, and adds to the queue every link associated
**   with that room, besides duplicates.
*/

void	explore_room(t_queue **queue, t_queue *queue_node, t_rooms *room)
{
	t_queue	*temp_queue;
	t_links	*temp_link;
	int		links;

	temp_queue = *queue;
	temp_link = room->links;
	queue_node->visited = true;
	if (room->links == NULL)
		return ;
	queue_node->start = room->start;
	queue_node->end = room->end;
	links = 0;
	while (temp_link)
	{
		if (is_dupe(queue, temp_link->name) && links++ == 1 && !temp_link->next)
			temp_queue->valid = false;
		else if (!is_dupe(queue, temp_link->name))
		{
			while (temp_queue->next != NULL)
				temp_queue = temp_queue->next;
			temp_queue->next = create_queue_node(*queue, temp_link->name);
			temp_queue->next->previous = temp_queue;
		}
		temp_link = temp_link->next;
	}
}
