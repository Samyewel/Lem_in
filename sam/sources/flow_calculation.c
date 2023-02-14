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
			graph[heads->room[y]->id][heads->room[y]->links[x]->id] = 1;
	}
}

static void	initialise_flow(t_data *data, t_heads *heads)
{
	int	**graph;
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
		while (++x < data_room_count)
		{
			graph[y][x] = 0;
			residual[y][x] = 0;
		}
	}
	heads->graph = graph;
	heads->residual = residual;
	populate_graph(data, heads);
}

static bool bfs(t_heads *heads, bool *visited, int start)
{
	int 	i;
	int		*queue;
	bool	*visited;

	queue = init_queue(heads->data->room_count);
	visited = (bool *)malloc(sizeof(bool) * data->room_count);
	if (!visited || !queue)
		clean_lem_in(heads, "Memory allocation failure in bfs.");
	ft_memset(visited, false, heads->data->room_count);
	enqueue(queue, heads->data->room_count, start);
	visited[start] = true;
	while (!is_empty(queue))
	{
		current = queue->data(queue->head);
		dequeue(queue);
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
}

void bfs_rooms(t_data *data, t_heads *heads)
{
	int start_room;
	bool *visited;

	initialise_flow(data, heads);
	start_room = find_start_room(heads);
	end_room = find_end_room(heads);
	visited = (bool *)malloc(sizeof(bool) * data->room_count);
	if (!visited)
		clean_lem_in(heads, "Memory allocation failure in bfs_rooms.");
	ft_memset(visited, false, data->room_count);
	bfs(heads, visited, start_room);
	free(visited);
	if (heads->path == NULL)
		clean_lem_in(heads, "No paths found.");
}
