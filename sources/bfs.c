/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:51:24 by sam               #+#    #+#             */
/*   Updated: 2022/11/28 17:23:48 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool	bfs(t_rooms **rooms)
{
	t_queue	*queue;
	t_rooms	*temp_room;
	t_links *link;
	t_queue	*temp_queue;

	queue = NULL;
	temp_queue = NULL;
	temp_room = find_start_room(rooms);
	queue = create_queue_node(queue, temp_room->name);
	//queue = add_to_queue(queue, temp_room->name);
	link = NULL;
	if (temp_room->links == NULL)
		ft_printf_strerror("No links from start");
	/*does end have a name/room assigned to it*/
	while (!is_empty(&queue)) // while end doesnthave (we havent checked all)
	{
		if (temp_room->links != NULL)
		{
			link = temp_room->links;
			while (link)
			{
				temp_queue = queue;
				while (temp_queue->next != NULL)
					temp_queue = temp_queue->next;
				temp_queue->next = create_queue_node(queue, link->name);
				//queue->next = add_to_queue(queue, link->name);
				link = link->next;
			}
		}
		queue->visited = true;
		if (queue->next != NULL)
			queue = queue->next;
		temp_room = visit_next(&queue, rooms);
	}
	return (is_empty(&queue));
}
