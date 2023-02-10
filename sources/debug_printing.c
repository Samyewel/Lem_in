/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:29:43 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/10 11:38:14 by sam              ###   ########.fr       */
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
	if (DEBUG == true && ROOMS == true)
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

void	print_path(t_paths *path)
{
	int	i;

	i = -1;
	if (DEBUG == true && PATHS == true)
	{
		ft_printf("Path: %d, Length: %d , usage: %d\n", path->nb, \
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

void	print_paths(t_paths **paths)
{
	int	i;

	i = -1;
	if (DEBUG == true && PATHS == true)
	{
		while (++i < MAX_SIZE)
		{
			if (paths[i] == NULL)
				return ;
			print_path(paths[i]);
		}
	}
}

/*
** print_solution:
** - Prints the solution containing their non-intersecting paths.
*/

void	print_solution(t_solutions *solution)
{
	int	i;

	i = -1;
	if (DEBUG == true && SOLUTIONS == true)
	{
		ft_printf("Solution[%d], length: %d, Paths:\n", \
			solution->nb, solution->total_length);
		if (solution->path == NULL)
		{
			while (++i < MAX_SIZE)
			{
				if (solution->path_indexes[i] >= 0)
					ft_printf("%d ", solution->path_indexes[i]);
				else
					break ;
			}
			ft_printf("\n");
		}
		else
			print_paths(solution->path);
	}
}
