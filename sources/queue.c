/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:22:53 by sam               #+#    #+#             */
/*   Updated: 2022/12/09 18:07:10 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** create_queue_node:
** - Allocates a fresh link to be added to the queue, setting the name
**   as the room name given as a variable.
*/

t_queue	*add_to_queue(t_queue *queue, char *room_name, t_queue *prev, int depth)
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
	queue->valid = true;
	return (queue);
}

/*
** is_empty:
** - Scans the queue and checks whether every room has been visited.
*/

int	is_empty(t_queue **queue)
{
	t_queue	*temp_queue;

	temp_queue = *queue;
	while (temp_queue)
	{
		if (temp_queue->visited == false)
			return (0);
		temp_queue = temp_queue->next;
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

void	explore_room(t_queue **queue_head, t_queue *queue, t_rooms *room)
{
	t_queue	*temp_queue;
	t_links	*temp_link;
	int		links;

	temp_queue = *queue_head;
	temp_link = room->links;
	queue->visited = true;
	if (room->links == NULL)
		return ;
	queue->start = room->start;
	queue->end = room->end;
	links = 0;
	while (temp_link)
	{
		if (++links == 1 && !temp_link->next && (!queue->start && !queue->end))
			queue->valid = false;
		if (!is_dupe(queue_head, temp_link->name))
		{
			while (temp_queue->next != NULL)
				temp_queue = temp_queue->next;
			temp_queue->next = add_to_queue(queue, temp_link->name, \
					temp_queue, queue->depth + 1);
		}
		temp_link = temp_link->next;
	}
}