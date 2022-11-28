/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:51:24 by sam               #+#    #+#             */
/*   Updated: 2022/11/28 16:51:35 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool	bfs(t_rooms **rooms)
{
	t_queue	*queue;
	t_rooms	*temp;
	t_links *link;

	queue = NULL;
	temp = find_start_room(rooms);
	queue = create_queue_node(queue, temp->name);
	//queue = add_to_queue(queue, temp->name);
	link = NULL;
	if (temp->links == NULL)
		ft_printf_strerror("No links from start");
	/*does end have a name/room assigned to it*/
	while (!is_empty(&queue)) // while end doesnthave (we havent checked all)
	{
		if (temp->links != NULL)
		{
			link = temp->links;
			while (link)
			{
				queue->next = create_queue_node(queue, link->name);
				//queue->next = add_to_queue(queue, link->name);
				link = link->next;
			}
		}
		queue->visited = true;
		if (queue->next != NULL)
			queue = queue->next;
		temp = visit_next(&queue, rooms);
	}
	return (is_empty(&queue));
}
