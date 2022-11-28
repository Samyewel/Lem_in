/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:51:24 by sam               #+#    #+#             */
/*   Updated: 2022/11/28 14:52:17 by sam              ###   ########.fr       */
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

t_queue	*initialise_queue_node(t_queue *queuem))
{
	queue = (t_queue *)malloc(sizeof(t_queue));
	queue->name = NULL;
	queue->next = NULL;
	queue->checked = FALSE;
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
		if (queue->checked)
			return (0);
		queue = queue->next;
	}
	return (1);
}

static int	bfs(t_rooms **rooms)
{
	t_queue	*queue;
	t_rooms	*start;
	t_rooms	*temp;

	start = find_start_room(&rooms);
	temp = start;
	queue = initialise_queue_node(queue);
	queue = add_to_queue(queue, start->name);

	/*does end have a name/room assigned to it*/
	while (!is_empty(&queue)) // while end doesnthave (we havent checked all)
	{
		//check_links(que, tail)
		queue = queue->next;
	}
}
