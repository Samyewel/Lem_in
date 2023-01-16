/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_flow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:51:24 by sam               #+#    #+#             */
/*   Updated: 2023/01/16 22:27:21 by sam              ###   ########.fr       */
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

static int	find_min_flow_on_path(t_queue *path)
{
	int		min_flow;
	t_queue	*temp_node;

	min_flow = INT_MAX;
	temp_node = path;
	while (temp_node)
	{
		if (!temp_node->start && !temp_node->end)
			min_flow = ft_min(min_flow, temp_node->flow);
		if (DEBUG == true && FLOWS == true)
		{
			ft_printf("%s[%d]", temp_node->name, temp_node->flow);
			if (!temp_node->end)
				ft_printf("->");
			else
				ft_printf("\n");
		}
		temp_node = temp_node->next;
	}
	return (min_flow);
}

static int	edmonds_karp(t_heads *heads, t_data *data)
{
	t_paths		*backtracked_paths;
	t_paths		*temp_path;
	int			min_flow;
	int			path_flow;

	backtracked_paths = bfs_process(heads, data);
	if (!backtracked_paths)
		ft_printf_strerror("No paths created in edmonds_karp.");
	temp_path = backtracked_paths;
	min_flow = INT_MAX;
	while (temp_path)
	{
		path_flow = find_min_flow_on_path(temp_path->path);
		min_flow = ft_min(min_flow, path_flow);
		temp_path = temp_path->next;
	}
	return (min_flow);
}

/*
** find_max_flow
** -
*/

int	calculate_flow(t_heads *heads, t_data *data)
{
	int	min_flow;

	min_flow = edmonds_karp(heads, data);
	ft_printf("Minimum flow = %lld\n", min_flow);
	return (min_flow);
}
