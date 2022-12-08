/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_flow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:51:24 by sam               #+#    #+#             */
/*   Updated: 2022/12/08 18:42:21 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** bfs:
** -
*/

static t_queue	*bfs(t_rooms **rooms)
{
	bool	end_visited;
	t_rooms	*temp_room;
	t_queue	*queue;
	t_queue	*temp_queue;

	end_visited = false;
	queue = NULL;
	temp_room = find_start_room(rooms);
	queue = create_queue_node(queue, temp_room->name);
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

static t_queue	*bfs_process(t_rooms *rooms)
{
	t_queue	*queue;
	t_queue	*backtraced_queue;

	queue = bfs(&rooms);
	if (!queue)
		ft_printf_strerror("No end found.");
	if (DEBUG == true)
		print_queue(&queue);
	backtraced_queue = backtrace_queue(&queue, &rooms, rooms);
	clean_queue(&queue);
	return (backtraced_queue);
}

/*
** edmonds_karp:
** -
*/

static int	edmonds_karp(t_rooms *rooms)
{
	t_queue	*queue;
	t_links	*paths;
	int		flow;

	queue = NULL;
	paths = NULL;
	flow = 0;
	while (1)
	{
		queue = bfs_process(rooms);
		if (flow == 1) // Prevent infinite loop until functional
			break ;
		flow++;
		//save paths here
		clean_queue(&queue);
	}
	return (flow);
}

int	find_max_flow(t_rooms *rooms)
{
	int	max_flow;

	max_flow = edmonds_karp(rooms);
	if (max_flow <= 0)
	{
		return (0);
	}
	return (1);
}
