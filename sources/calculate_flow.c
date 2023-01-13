/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_flow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:51:24 by sam               #+#    #+#             */
/*   Updated: 2023/01/13 12:57:08 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** bfs:
** -
*/

static t_queue	*bfs(t_rooms **rooms)
{
	t_queue		*queue;
	t_queue		*temp_queue;
	t_rooms		*temp_room;
	bool		end_visited;

	end_visited = false;
	queue = NULL;
	temp_room = find_start_room(rooms);
	queue = create_queue(queue, temp_room->name, NULL, 0);
	if (!queue)
		ft_printf_strerror("Memory allocation failure in bfs");
	temp_queue = queue;
	if (temp_room->links == NULL)
		ft_printf_strerror("No links from start");
	while (!is_empty(&queue))
	{
		explore_room(&queue, temp_queue, temp_room);
		end_visited += (temp_room->end && temp_queue->visited);
		temp_room = visit_next(&queue, rooms);
		temp_queue = temp_queue->next;
	}
	if (!end_visited)
		return (NULL);
	return (queue);
}

/*
** bfs_process:
** -
*/

static t_paths	*bfs_process(t_heads *heads, t_data *data)
{
	t_paths	*backtracked_queue;

	heads->queue_head = bfs(&heads->rooms_head);
	if (!heads->queue_head)
		ft_printf_strerror("No end found.");
	if (DEBUG == true && QUEUE == true)
		print_queue(&heads->queue_head);
	reset_visted(&heads->queue_head);
	backtracked_queue = backtrack_queue(heads, data);
	clean_queue(&heads->queue_head);
	return (backtracked_queue);
}

/*
** edmonds_karp:
** -
*/

static int	edmonds_karp(t_heads *heads, t_data *data)
{
	t_paths	*queue;
	t_paths	*paths;
	int		flow;

	queue = NULL;
	paths = NULL;
	if (paths == NULL || queue == NULL)
		ft_printf(""); // Surpress warnings
	flow = 0;
	while (1)
	{
		queue = bfs_process(heads, data);
		if (flow == 0) // Prevent infinite loop until functional
			break ;
		flow++;
		//save paths here
		clean_queue(&heads->queue_head);
	}
	return (flow);
}

/*
** find_max_flow
** -
*/

int	find_max_flow(t_heads *heads, t_data *data)
{
	int	max_flow;

	max_flow = edmonds_karp(heads, data);
	if (max_flow <= 0)
	{
		return (0);
	}
	return (1);
}
