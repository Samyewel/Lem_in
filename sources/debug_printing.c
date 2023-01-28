/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:29:43 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/28 15:03:01 by swilliam         ###   ########.fr       */
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

void	print_rooms(t_rooms **rooms)
{
	t_rooms	*ptr;
	t_links	*link;

	ptr = *rooms;
	if (DEBUG == true && ROOMS == true)
	{
		while (ptr)
		{
			ft_printf("Name: %s\n", ptr->name);
			ft_printf("x: %d\ny: %d\n", ptr->coord_x, ptr->coord_y);
			ft_printf("Start? %d\nEnd? %d\n", ptr->start, ptr->end);
			link = ptr->links;
			while (link)
			{
				ft_printf("Links to: %s\n", link->name);
				link = link->next;
			}
			ft_printf("\n");
			ptr = ptr->next;
		}
	}
}

void	print_paths(t_paths **path_list)
{
	t_paths	*temp_path_list;
	t_rooms	*temp_path;

	temp_path_list = *path_list;
	if (DEBUG == true && PATHS == true)
	{
		while (temp_path_list)
		{
			ft_printf("Path[%d]: ", temp_path_list->nb);
			temp_path = temp_path_list->path;
			while (temp_path)
			{
				if (temp_path->end)
					ft_printf("%s\n", temp_path->name);
				else
					ft_printf("%s->", temp_path->name);
				temp_path = temp_path->next;
			}
			temp_path_list = temp_path_list->next;
		}
	}
}

void	print_solutions(t_heads *heads)
{
	t_solutions	*temp_solution;
	int			i;

	i = 0;
	temp_solution = heads->solutions;
	if (DEBUG == true && SOLUTIONS == true)
	{
		while (temp_solution)
		{
			i = -1;
			ft_printf("Solution[%d], length: %d, Paths:\n", \
			temp_solution->nb, temp_solution->total_length);
			while (++i < MAX_SIZE)
			{
				if (temp_solution->path_indexes[i] >= 0)
					ft_printf("%d ", temp_solution->path_indexes[i]);
				else
					break ;
			}
			ft_printf("\n");
			temp_solution = temp_solution->next;
		}
	}
}
