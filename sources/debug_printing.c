/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:29:43 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/21 15:22:08 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** print_rooms:
** - Prints all stored rooms and relevant links.
*/

void	print_rooms(t_heads *heads)
{
	int	i;
	int	x;

	i = -1;
	if (heads->flags->rooms == true)
	{
		while (++i < MAX_SIZE)
		{
			if (heads->room[i] == NULL)
				break ;
			ft_printf("ID: %d ", heads->room[i]->id);
			ft_printf("Name: %s\n", heads->room[i]->name);
			ft_printf("Start? %d\n", heads->room[i]->start);
			ft_printf("End? %d\n", heads->room[i]->end);
			x = -1;
			ft_printf("Links:\n");
			while (++x < MAX_SIZE)
			{
				if (heads->room[i]->links[x] == NULL)
					break ;
				ft_printf("%s ", heads->room[i]->links[x]->name);
			}
			ft_printf("\n\n");
		}
	}
}

/*
** print_path:
** - Prints all nodes of the given path.
*/

void	print_path(t_heads *heads, t_paths *path)
{
	int	i;

	i = -1;
	if (heads->flags->paths == true)
	{
		ft_printf("Path[%d], length: %d, usage: %d\n", path->nb, \
		path->length, path->usage);
		while (++i < MAX_SIZE)
		{
			if (path->room[i] == NULL)
				return ;
			if (path->room[i]->end)
				ft_printf("%s\n", path->room[i]->name);
			else
				ft_printf("%s->", path->room[i]->name);
		}
	}
}

/*
** print_paths:
** - Prints all paths given.
*/

void	print_paths(t_heads *heads, t_paths **paths)
{
	int	i;

	i = -1;
	if (heads->flags->paths == true)
	{
		while (++i < MAX_SIZE)
		{
			if (paths[i] == NULL)
				return ;
			print_path(heads, paths[i]);
		}
		ft_printf("\n");
	}
}

/*
** print_solution:
** - Prints the solution containing their non-intersecting paths.
*/

void	print_solution(t_heads *heads, t_solutions *solution)
{
	int	i;

	if (heads->flags->solutions == true)
	{
		ft_printf("Solution:\nAnts: %d | Paths: %d\n", \
		heads->data->ant_count, solution->paths_used);
		i = -1;
		while (++i < solution->path_count)
		{
			if (heads->flags->paths == false)
				ft_printf("%d ", solution->path_indexes[i]);
			else
				print_path(heads, solution->path[i]);
		}
		ft_printf("\n");
	}
}

/*
** print_graph:
** - Prints the content of the given graph.
*/

void	print_graph(t_heads *heads, int **graph)
{
	int	y;
	int	x;

	y = -1;
	x = -1;
	if (heads->flags->graph)
	{
		ft_printf("    ");
		while (++x < heads->data->room_count)
			ft_printf("%2.2s ", heads->room[x]->name);
		ft_printf("\n");
		while (++y < heads->data->room_count)
		{
			x = -1;
			ft_printf("%3.3s", heads->room[y]->name);
			while (++x < heads->data->room_count)
				ft_printf("%3d", graph[y][x]);
			ft_printf("\n");
		}
		ft_printf("\n");
	}
}
