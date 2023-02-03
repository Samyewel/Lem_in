/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:29:43 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/03 15:23:32 by swilliam         ###   ########.fr       */
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

void	print_path(t_paths *path)
{
	t_rooms	*temp_node;

	temp_node = path->path;
	if (DEBUG == true && PATHS == true)
	{
		ft_printf("Path[%d]: ", path->nb);
		while (temp_node)
		{
			if (temp_node->end)
				ft_printf("%s\n", temp_node->name);
			else
				ft_printf("%s->", temp_node->name);
			temp_node = temp_node->next;
		}
	}
}

void	print_paths(t_paths **path_list, int path_nb)
{
	t_paths	*temp_path;

	temp_path = *path_list;
	if (DEBUG == true && PATHS == true)
	{
		while (temp_path)
		{
			if (path_nb > 0)
			{
				if (temp_path->nb == path_nb)
				{
					print_path(temp_path);
					return ;
				}
			}
			else
				print_path(temp_path);
			temp_path = temp_path->next;
		}
	}
}

void	print_solutions(t_data *data, t_heads *heads)
{
	int	i;
	int	x;

	i = -1;
	x = -1;
	if (DEBUG == true && SOLUTIONS == true)
	{
		while (++i < data->path_count)
		{
			x = -1;
			ft_printf("Solution[%d], length: %d, Paths:\n", \
			heads->solutions[i]->nb, heads->solutions[i]->total_length);
			while (++x < MAX_SIZE)
			{
				if (heads->solutions[i]->path_indexes[x] >= 0)
					ft_printf("%d ", heads->solutions[i]->path_indexes[x]);
				else
					break ;
			}
			ft_printf("\n");
		}
	}
}
