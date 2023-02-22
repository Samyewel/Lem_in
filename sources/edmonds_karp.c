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
		clean_lem_in("Memory allocation failure in initialise_visited.");
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

static bool	bfs_return(t_heads *heads, bool ret, bool *visited, int end)
{
	if (ret == true)
		create_new_path(heads, end);
	free(visited);
	free(heads->queue->data);
	free(heads->queue);
	return (ret);
}

/*
** explore:
** - Explores the linked rooms.
*/

static void	explore(t_heads *heads, bool *visited, int current, int i)
{
	enqueue(heads->queue, heads->room[i]->id);
	visited[i] = true;
	heads->parent[i] = current;
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
	bool	*visited;
	int		c;
	int		ret;
	int		i;

	c = 0;
	ret = false;
	heads->queue = init_queue(heads->data->room_count);
	visited = initialise_bfs(heads, start);
	enqueue(heads->queue, start);
	while (!is_empty(heads->queue))
	{
		c = heads->queue->data[heads->queue->head];
		dequeue(heads->queue);
		i = -1;
		while (++i < heads->data->room_count)
		{
			if (heads->residual[c][i] == 1 && !visited[i] && !heads->stored[i])
				explore(heads, visited, c, i);
		}
		if (c == end)
			break ;
	}
	ret = (c == end);
	return (bfs_return(heads, ret, visited, end));
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
	int	i;

	start_room = find_start_room(heads);
	end_room = find_end_room(heads);
	initialise_edmonds_karp(data, heads);
	x = -1;
	i = 1;
	while (x < i)
	{
		print_graph(heads, heads->residual);
		while (bfs(heads, start_room, end_room))
		{
			update_visited(heads->stored, heads->path[++x]);
			print_path(heads, heads->path[x]);
			if (heads->path[x]->length == 2 || data->ant_count == 1)
				break ;
		}
		if (heads->path != NULL && i == 1)
			i = heads->path[data->bfs_path]->length - 1;
		if (!continue_bfs(heads, heads->parent, heads->stored))
			break ;
	}
}
