/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:29:43 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/08 14:27:58 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** print_data:
** - Prints all data that has been stored.
*/

void	print_data(t_data *data)
{
	if (DEBUG == true && DATA == true)
	{
		ft_printf("\nAnt count: %d\n", data->ant_count);
		ft_printf("\nRoom count: %d\n", data->room_count);
	}
}

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
			ft_printf("[%d]: %s\n", heads->room[i]->id, heads->room[i]->name);
			ft_printf("x: %d\ny: %d\n", heads->room[i]->coord_x, heads->room[i]->coord_y);
			ft_printf("Start? %d\nEnd? %d\n", heads->room[i]->start, heads->room[i]->end);
			x = -1;
			ft_printf("Links:\n");
			while (++x < MAX_SIZE)
			{
				if (heads->room[i]->links[x] == NULL)
					break ;
				ft_printf("%s", heads->room[i]->links[x]->name);
				if (heads->room[i]->links[x + 1] == NULL)
					ft_printf("\n");
				else
					ft_printf(", ");
			}
			ft_printf("\n");
		}
	}
}

void	print_path(t_paths *path)
{
	int	i;

	i = -1;
	if (DEBUG == true && PATHS == true)
	{
		ft_printf("Path[%d], Length: %d ", path->nb, path->length);
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

void	print_solution(t_solutions *solution)
{
	int	i;

	i = -1;
	if (DEBUG == true && SOLUTIONS == true)
	{
		ft_printf("Solution[%d], length: %d, Paths:\n", \
			solution->nb, solution->total_length);
		if (solution->paths == NULL)
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
			print_paths(solution->paths);
	}
}
