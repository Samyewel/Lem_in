/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:51:24 by sam               #+#    #+#             */
/*   Updated: 2022/11/28 15:49:46 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

typedef struct s_queue
{
	struct s_rooms	*name;
	struct s_queue	*next;
	bool			checked;
}	t_queue;

void	check_links(t_rooms *room, t_queue *queue)
{
	/*array of the links is needed
	need to check the flows
	*/
	t_links	*temp;
	t_rooms	link_array;
	temp = room;
	int i;

	i = 0;
	queue->name
	queue->next = find_links()
}

t_queue	*initialise_queue_node(t_queue *queue)
{
	queue = (t_queue *)malloc(sizeof(t_queue));
	queue->name = NULL;
	queue->next = NULL;
	queue->visited = FALSE;
	return (queue);
}

t_queue	*add_to_queue(t_queue *queue, char *room_name)
{
	queue->name = ft_strdup(room_name);
	return(queue)
}

int		is_empty(t_queue **queue)
{
	while (queue)
	{
		if (queue->visited == FALSE)
			return (0);
		queue = queue->next;
	}
	return (1);
}

t_rooms	*visit_next(t_queue **queue)
{
	t_queue *temp;

	temp = NULL;
	while (queue)
	{
		temp = find_room(&rooms, queue->name);
		if (queue->visited == FALSE)
			return (find_room(&rooms, queue->name));
		queue = queue->next;
	}
	return (NULL);
}

static int	bfs(t_rooms **rooms)
{
	t_queue	*queue;
	t_rooms	*start;
	t_rooms	*temp;
	t_links *link;

	temp = find_start_room(&rooms);
	queue = initialise_queue_node(queue);
	queue = add_to_queue(queue, temp->name);
	link = NULL;

	/*does end have a name/room assigned to it*/
	while (!is_empty(&queue)) // while end doesnthave (we havent checked all)
	{
		if (temp->links == NULL)
			ft_printf_strerror("No links from start");
		link = temp->links;
		while (link)
		{
			queue->next = initialise_queue_node(queue);
			queue->next = add_to_queue(queue, link->name);
			link = link->next;
		}
		queue->visited = TRUE;
		if (queue->next != NULL)
			queue = queue->next;
		temp = visit_next(&queue);
		//check_links(que, tail)
	}
}
