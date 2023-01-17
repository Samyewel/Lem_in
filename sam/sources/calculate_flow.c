/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   calculate_flow.c								   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sam <sam@student.42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/11/28 13:51:24 by sam			   #+#	#+#			 */
/*   Updated: 2023/01/17 12:27:04 by sam			  ###   ########.fr	   */
/*																			*/
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

static void	find_path_flow(t_queue *path, int flow)
{
	t_queue	*temp_node;

	temp_node = path;
	while (temp_node)
	{
		if (!temp_node->start && !temp_node->end)
			flow = ft_min(flow, temp_node->capacity - temp_node->edge_flow);
		temp_node = temp_node->next;
	}
}

/*
** find_max_flow:
** - Finds the maximum flow of the graph using all possible path solutions.
*/

static int	find_max_flow(t_paths **paths, t_data *data)
{
	t_paths	*temp_path;
	t_queue	*temp_node;

	temp_path = *paths;
	while (temp_path)
	{
		temp_path->path_flow = 1;
		find_path_flow(temp_path->path, temp_path->path_flow);
		temp_node = temp_path->path;
		if (DEBUG == true && FLOWS == true)
			ft_printf("Path[%d]:\n", temp_path->path_nb);
		while (temp_node)
		{
			temp_node->edge_flow += temp_path->path_flow;
			if (!temp_node->start)
				temp_node->previous->edge_flow -= temp_path->path_flow;
			print_flows(temp_path->path);
			temp_node = temp_node->next;
		}
		data->max_flow += temp_path->path_flow;
		temp_path = temp_path->next;
	}
	return (data->max_flow);
}

/*
** calculate_flow
** - Uses the bfs to confirm a path through the start and end nodes.
** - Stores all possible paths by backtracking the graph.
** - Calls find_max_flow to calculate the max flow of the graph to later
**   find the optimal combinations of paths from start to end.
*/

int	calculate_flow(t_heads *heads, t_data *data)
{
	int		max_flow;

	heads->queue_head = bfs(&heads->rooms_head);
	if (!heads->queue_head)
		ft_printf_strerror("No end found.");
	print_queue(&heads->queue_head);
	backtrack_queue(heads, data);
	clean_queue(&heads->queue_head);
	max_flow = find_max_flow(&heads->paths_head, data);
	if (DEBUG == true && FLOWS == true)
		ft_printf("Max flow = %d\n", max_flow);
	return (max_flow);
}
