/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_flow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:51:24 by sam               #+#    #+#             */
/*   Updated: 2023/01/16 13:34:55 by sam              ###   ########.fr       */
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
	backtracked_queue = backtrack_queue(heads, data);
	clean_queue(&heads->queue_head);
	return (backtracked_queue);
}

/*
** edmonds_karp:
** -
*/

static void	update_flow(t_paths *path, int flow)
{
	t_queue	*temp_queue;

	if (!path)
		return ;
	temp_queue = path->path;
	while (temp_queue)
	{
		temp_queue->flow = flow;
		temp_queue = temp_queue->next;
	}
}

static int	edmonds_karp(t_heads *heads, t_data *data)
{
	t_paths	*backtracked_path;
	int		max_flow;

	backtracked_path = NULL;
	max_flow = 0;
	while (1)
	{
		backtracked_path = bfs_process(heads, data);
		if (!backtracked_path)
			break ;
		update_flow(backtracked_path, max_flow + 1);
		max_flow++;
		clean_paths(heads);
	}
	return (max_flow);
}

/*
** find_max_flow
** -
*/

int	find_max_flow(t_heads *heads, t_data *data)
{
	int	max_flow;

	max_flow = edmonds_karp(heads, data);
	return (max_flow);
}
