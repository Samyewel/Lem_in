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

/*
** initialise_bfs:
** - Initialises the necessary data to begin the BFS process.
*/

static bool	*initialise_bfs(t_heads *heads, int start_room)
{
	bool	*visited;

	visited = NULL;
	visited = (bool *)malloc(sizeof(bool) * heads->data->room_count);
	if (!visited)
		clean_lem_in(heads, "Memory allocation failure in initialise_visited.");
	ft_memset(visited, false, heads->data->room_count);
	ft_memset(heads->parent, -1, heads->data->room_count);
	visited[start_room] = true;
	heads->parent[start_room] = -1;
	return (visited);
}

/*
** bfs_return:
** - Used to save lines when ending the BFS process.
*/

static bool	bfs_return(bool ret, bool *visited, t_queue *queue)
{
	free (visited);
	free (queue);
	return (ret);
}

/*
** bfs:
** - Finds the shortest path between the start to end nodes if one exists.
** - Tracks the parent of each node so that the path can be backtracked during
**   path creation.
** - Adds rooms to a queue, removing them once their links have been checked.
** - Checks the residual graph to see that an available edge between each node
**   is available to be used, then checks the visited array in heads to ensure
**   a room is not already used in a path.
*/

static bool	bfs(t_heads *heads, int start, int end)
{
	int		i;
	int		current;
	t_queue	*queue;
	bool	*visited;
	int		ret;

	current = 0;
	ret = false;
	queue = init_queue(heads, heads->data->room_count);
	if (!queue)
		clean_lem_in(heads, "Memory allocation failure in bfs.");
	visited = initialise_bfs(heads, start);
	enqueue(queue, start);
	while (!is_empty(queue))
	{
		current = queue->data[queue->head];
		dequeue(queue);
		i = -1;
		while (++i < heads->data->room_count)
		{
			if (heads->residual[current][i] == 1 && !visited[i] && \
				!heads->visited[i])
			{
				enqueue(queue, heads->room[i]->id);
				visited[i] = true;
				heads->parent[i] = current;
			}
		}
		if (current == end)
		{
			ret = true;
			create_new_path(heads, end);
			break ;
		}
	}
	return (bfs_return(ret, visited, queue));
}

/*
** edmonds_karp:
** - Creates the visited array to store all rooms used in paths created via
**   the BFS.
** - Creates the parent array which contains the parent of each node being
**   stored in a path.
** - Loops the BFS until there are no more augmenting paths to be found.
** - Updates the residual graph so that the next BFS process cannot use a
**   room that already exists in a path.
*/

void	edmonds_karp(t_data *data, t_heads *heads)
{
	int	start_room;
	int	end_room;
	int	x;

	start_room = find_start_room(heads);
	end_room = find_end_room(heads);
	heads->parent = (int *)malloc(sizeof(int) * data->room_count);
	heads->visited = (bool *)malloc(sizeof(bool) * data->room_count);
	if (!heads->parent || !heads->visited)
		clean_lem_in(heads, "Memory allocation failure in edmonds_karp.");
	ft_memset(heads->visited, false, data->room_count);
	initialise_graphs(data, heads);
	x = -1;
	while (bfs(heads, start_room, end_room))
	{
		print_graph(heads, heads->residual);
		update_residual(heads->residual, heads->visited, heads->path[++x]);
		print_graph(heads, heads->residual);
	}
	print_paths(heads->path);
}
