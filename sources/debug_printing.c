/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:29:43 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/06 15:19:50 by sam              ###   ########.fr       */
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
		ft_printf("Printing rooms...\n");
		while (++i < MAX_SIZE)
		{
			if (heads->room_array[i] == NULL)
				break ;
			ft_printf("Name: %s\n", heads->room_array[i]->name);
			ft_printf("x: %d\ny: %d\n", heads->room_array[i]->coord_x, heads->room_array[i]->coord_y);
			ft_printf("Start? %d\nEnd? %d\n", heads->room_array[i]->start, heads->room_array[i]->end);
			x = -1;
			while (++x < MAX_SIZE)
			{
				if (heads->room_array[i]->links[x] == NULL)
					break ;
				ft_printf("Links to: %s\n", heads->room_array[i]->links[x]->name);
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
		ft_printf("Path %d [%d] ", path->nb, path->length);
		while (++i < MAX_SIZE)
		{
			if (path->path[i] == NULL)
				return ;
			if (path->path[i]->end)
				ft_printf("%s\n", path->path[i]->name);
			else
				ft_printf("%s->", path->path[i]->name);
		}
	}
}

void	print_paths(t_heads *heads)
{
	int	i;

	i = -1;
	if (DEBUG == true && PATHS == true)
	{
		while (++i < MAX_SIZE)
		{
			if (heads->path_array[i] == NULL)
				return ;
			print_path(heads->path_array[i]);
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
		while (++i < MAX_SIZE)
		{
			if (solution->path_indexes[i] >= 0)
				ft_printf("%d ", solution->path_indexes[i]);
			else
				break ;
		}
		ft_printf("\n");
	}
}
