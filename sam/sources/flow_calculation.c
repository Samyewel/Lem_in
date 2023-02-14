/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   flow_calculation.c								 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sam <sam@student.42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/02/13 18:57:49 by sam			   #+#	#+#			 */
/*   Updated: 2023/02/13 19:19:40 by sam			  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "lem_in.h"

static void	populate_graph(t_data *data, t_heads *heads)
{
	int	y;
	int	x;

	y = -1;
	while (++y < data->room_count)
	{
		x = -1;
		if (heads->room[y]->links == NULL)
			continue ;
		while (++x < MAX_SIZE && heads->room[y]->links[x] != NULL)
			heads->graph[heads->room[y]->id][heads->room[y]->links[x]->id] = 1;
	}
}

static bool *initialise_visited(t_heads *heads, int start_room)
{
	bool *visited;

	visited = NULL;
	visited = (bool *)malloc(sizeof(bool) * heads->data->room_count);
	if (!visited)
		clean_lem_in(heads, "Memory allocation failure in initialise_visited.");
	ft_memset(visited, false, heads->data->room_count);
	visited[start_room] = true;
	return (visited);
}

static void	initialise_flow(t_data *data, t_heads *heads)
{
	int	**graph;
	int	**residual;
	int	y;
	int	x;

	graph = NULL;
	residual = NULL;
	graph = ft_make_grid(data->room_count, data->room_count);
	residual = ft_make_grid(data->room_count, data->room_count);
	if (!graph || !residual)
		clean_lem_in(heads, "Memory allocation failure in flow_network.");
	y = -1;
	while (++y < data->room_count)
	{
		x = -1;
		while (++x < data->room_count)
		{
			graph[y][x] = 0;
			residual[y][x] = 0;
		}
	}
	heads->graph = graph;
	heads->residual = residual;
	populate_graph(data, heads);
}

static bool bfs(t_heads *heads, int start, int end)
{
	int 	i;
	int		current;
	t_queue	*queue;
	bool	*visited;

	current = 0;
	queue = init_queue(heads, heads->data->room_count);
	visited = initialise_visited(heads, start);
	enqueue(queue, start);
	while (!is_empty(queue))
	{
		current = queue->data[queue->head];
		dequeue(queue);
		i = -1;
		while (++i < heads->data->room_count)
		{
			if (heads->graph[current][i] == 1 && !visited[i])
			{
				enqueue(queue, i);
				visited[i] = true;
			}
		}
	}
	free(queue);
	if (visited[end])
	{
		free(visited);
		return (true);
	}
	return (false);
}

void flow_calculation(t_data *data, t_heads *heads)
{
	int start_room;
	int	end_room;

	initialise_flow(data, heads);
	start_room = find_start_room(heads);
	end_room = find_end_room(heads);
	bfs(heads, start_room, end_room);
	if (heads->path == NULL)
		clean_lem_in(heads, "No paths found.");
}
