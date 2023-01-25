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

static void	populate_matrix(t_heads *heads, int **graph)
{
	t_paths	*temp_path;
	t_rooms	*temp_node;
	int		x;
	int		y;

	x = 0;
	y = 0;
	temp_path = heads->paths;
	while (temp_path)
	{
		temp_node = temp_path->path;
		while (temp_node)
		{
			if (temp_node->next != NULL)
			{
				y = get_index(heads->hash_table, temp_node->name);
				x = get_index(heads->hash_table, temp_node->next->name);
				if (y < 0 || x < 0)
					ft_printf_strerror("Error during index search");
				graph[y][x] += (graph[y][x] == 0);
			}
			temp_node = temp_node->next;
		}
		temp_path = temp_path->next;
	}
}

static void	update_flow(
int **graph,
int size,
int start,
int end)
{
	int	current;
	int	i;

	current = end;
	while (current != start)
	{
		i = -1;
		while (++i < size)
		{
			if (graph[i][current] > 0 && graph[i][current] < graph[current][i])
			{
				graph[i][current]++;
				current = i;
				break;
			}
		}
	}
}

int	bfs(t_heads *heads, int **graph, int start, int end)
{
	t_queue	*queue;
	bool	visited[heads->hash_table->size];
	int		current;
	int		i;

	queue = NULL;
	queue = init_queue(heads->hash_table->size);
	ft_bzero(visited, sizeof(visited));
	enqueue(queue, heads->hash_table->size, start);
	// print_queue(queue, heads->hash_table->size);
	while (!is_empty(queue))
	{
		current = queue->data[queue->head];
		print_queue(queue, heads->hash_table->size);
		dequeue(queue);
		print_queue(queue, heads->hash_table->size);
		if (current == end)
			return (1);
		i = 0;
		while (i < heads->hash_table->size)
		{
			if (graph[current][i] > 0 && !visited[i])
			{
				visited[i] = true;
				enqueue(queue, heads->hash_table->size, i);
			}
			i++;
		}
	}
	return (0);
}

static void	optimise_paths(t_heads *heads, t_data *data)
{
	int		**graph;
	int		size;
	int		flow;
	int		start;
	int		end;

	if (data)
		ft_printf(""); //surpress
	size = heads->hash_table->size;
	graph = ft_make_grid(size, size);
	if (!graph)
		ft_printf_strerror("Memory allocation failure in optimise_paths.");
	populate_matrix(heads, graph);
	start = get_index(heads->hash_table, find_start_room(&heads->rooms)->name);
	end = get_index(heads->hash_table, find_end_room(&heads->rooms)->name);
	ft_printf("start index = %d, end index = %d\n", start, end);
	flow = 0;
	if (start || end || flow)
		ft_printf("");
	while (bfs(heads, graph, start, end))
	{
		//ft_printf("bfs...\n");
		update_flow(graph, size, start, end);
		//print_graph(heads, graph, size, size);
		flow++;
	}
	print_graph(heads, graph, size, size);
	clean_adjacency_matrix(graph, size);
}

/*
** calculate_flow
** - Uses the bfs to confirm a path through the start and end nodes.
** - Stores all possible paths by backtracking the graph.
** - Calls find_max_flow to calculate the max flow of the graph to later
**   find the optimal combinations of paths from start to end.
*/

void	calculate_flow(t_heads *heads, t_data *data)
{
	// heads->queue_head = bfs_confirm_path(&heads->rooms_head);
	// if (!heads->queue_head)
	// 	ft_printf_strerror("No end found.");
	// print_queue(&heads->queue_head);
	// clean_queue(&heads->queue_head);
	backtrack(heads, data);
	print_paths(&heads->paths);
	store_paths_in_hash_table(heads);
	print_hash_table(heads->hash_table);
	optimise_paths(heads, data);
	clean_hash_table(heads->hash_table);
	//ft_printf("disjoint_count = %d\n", disjoint_count);
}
