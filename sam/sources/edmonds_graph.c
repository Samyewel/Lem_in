/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_graph.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:31:31 by sam               #+#    #+#             */
/*   Updated: 2023/02/19 15:34:42 by sam              ###   ########.fr       */
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

void	initialise_graphs(t_data *data, t_heads *heads)
{
	int	**residual;
	int	y;
	int	x;

	residual = NULL;
	residual = ft_make_grid(data->room_count, data->room_count);
	if (!residual)
		clean_lem_in("Memory allocation failure in flow_network.");
	y = -1;
	while (++y < data->room_count)
	{
		x = -1;
		while (++x < data->room_count)
			residual[y][x] = 0;
	}
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

void	update_residual(int **residual, bool *visited, t_paths *path)
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
		residual[from][to]--;
		residual[to][from]++;
	}
}
