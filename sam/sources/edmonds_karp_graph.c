/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp_graph.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:31:31 by sam               #+#    #+#             */
/*   Updated: 2023/02/21 15:28:18 by swilliam         ###   ########.fr       */
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
	path_len = heads->path[path_nb]->length - 1;
	cut = ++heads->path[path_nb]->bfs_index;
	if (heads->path[0] == NULL)
		clean_lem_in("No Paths found");
	to = heads->path[path_nb]->room[path_len - cut - 1]->id;
	from = heads->path[path_nb]->room[path_len - cut]->id;
	if (from <= 0 || to <= 1)
		return (0);
	ft_memset(parent, -1, heads->data->room_count);
	ft_memset(stored, false, heads->data->room_count);
	heads->residual[to][from] = 0;
	return (1);
}
