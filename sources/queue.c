/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:22:53 by sam               #+#    #+#             */
/*   Updated: 2022/11/29 14:49:44 by swilliam         ###   ########.fr       */
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
	queue->visited = false;
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

int	is_duplicate(t_queue **queue, char *link_name)
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

	temp_queue = *queue;
	// Pointer to the head of the queue.
	temp_link = NULL;
	queue_node->visited = true;
	// Confirm that we have now visited this room.
	if (room->links == NULL)
		return ;
	// If the current room has no links, exit the function
	temp_link = room->links;
	// Point to the head of the list of links of the current room
	while (temp_link)
	// Loop through the links of the current room
	{
		if (!is_duplicate(queue, temp_link->name))
		// checks name is not already in queue
		{
			while (temp_queue->next != NULL)
				temp_queue = temp_queue->next;
			// Loops through queue to the tail of the list
			temp_queue->next = create_queue_node(*queue, temp_link->name);
			// Adds a node to the tail of the queue
		}
		temp_link = temp_link->next;
		// Iterate to the next link in the list
	}
}
