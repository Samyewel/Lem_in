/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp_graph.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:31:31 by sam               #+#    #+#             */
/*   Updated: 2023/02/21 18:22:04 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** populate_graph:
** - Fills the graph with each edge, where y is the parent, and x is the child.
*/

void	populate_graph(t_data *data, t_heads *heads, int **graph)
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

/*
** initialise_graphs:
** - Creates a square graph containing the ID of each room on both axis.
*/

void	initialise_graph(t_data *data, t_heads *heads)
{
	int	**residual;

	residual = NULL;
	residual = ft_make_grid(data->room_count, data->room_count);
	if (!residual)
		clean_lem_in("Memory allocation failure in flow_network.");
	heads->residual = residual;
	populate_graph(data, heads, heads->residual);
}

/*
** initialise_edmonds_karp:
** - Initialises the Edmonds-Karp process to save lines within the function.
*/
void	initialise_edmonds_karp(t_data *data, t_heads *heads)
{
	heads->parent = (int *)malloc(sizeof(int) * heads->data->room_count);
	heads->stored = (bool *)ft_memalloc(sizeof(bool) * heads->data->room_count);
	initialise_graph(data, heads);
	if (!heads->parent || !heads->stored || !heads->residual)
		clean_lem_in("Memory allocation failure in edmonds_karp.");
}

/*
** update_residual:
** - When a path is stored via the BFS, we remove the link from the residual
**   graph so that it is not checked again later in the process.
** - We add that removed link to the opposite side of the graph so that the
**   relation is not lost.
*/

void	update_visited(bool *visited, t_paths *path)
{
	int	i;
	int	from;
	int	to;

	i = -1;
	while (++i < path->length - 1)
	{
		from = path->room[i]->id;
		to = path->room[i + 1]->id;
		if (!path->room[i + 1]->end)
			visited[to] = true;
	}
}

int	continue_bfs(t_heads *heads, int *parent, bool *stored)
{
	int	path_nb;
	int	path_len;
	int	cut;
	int	to;
	int	from;

	path_nb = heads->data->bfs_path;
	if (path_nb > 0 && heads->data->bfs_path >= heads->data->path_count - 1)
		return (0);
	path_len = heads->path[path_nb]->length - 1;
	if (path_len == 1 || heads->data->ant_count == 1)
		return (0);
	cut = ++heads->path[path_nb]->bfs_index;
	if (heads->path == NULL)
		clean_lem_in("No Paths found");
	to = heads->path[path_nb]->room[path_len - cut]->id;
	from = heads->path[path_nb]->room[path_len - cut - 1]->id;
	if (heads->room[from]->start)
		heads->data->bfs_path++;
	ft_memset(parent, -1, heads->data->room_count);
	ft_memset(stored, false, heads->data->room_count);
	heads->residual[from][to] = 0;
	return (1);
}
