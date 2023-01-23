/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_done.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:16:43 by egaliber          #+#    #+#             */
/*   Updated: 2023/01/23 15:25:16 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	give_first_path(t_ants *ants, t_paths *paths, t_heads *heads, int i)
{
	ants->room = heads->paths_head;
	if (ants->next != NULL)
		ants = ants->next;
	paths->path_usage_times--;
	paths->temp++;
	if (paths->path_usage_times == 0)
		i++;
	if (paths->next != NULL)
		paths = paths->next;
}

void	printer(t_ants *ants, t_heads *heads, t_paths *paths, t_data *data)
{
	int	i;

	while (data->finished != data->ant_count)
	{
		i = 0;
		paths = heads->paths_head;
		ants = heads->ants_head;
		while (i < data->number_of_paths && ants->has_moved == false \
				&& ants->has_finished == false)
			first_move(ants, paths, data, i, heads);
		ft_printf("\n");
		if (heads->ants_head->has_moved == true)
		{
			ants = heads->ants_head;
			while (ants->has_moved == true \
					&& data->finished != data->ant_count)
				move_played(ants, paths, data, heads);
		}
	}
}

void	give_ants_paths(t_ants *ants, t_paths *paths, t_data *data, \
						t_heads *heads)
{
	int	i;

	i = 0;
	paths = heads->paths_head;
	ants = heads->ants_head;
	while (i < data->number_of_paths)
	{
		while (paths->path_usage_times > 0)
		{
			if (paths == heads->paths_head && paths->path_usage_times > 0)
				give_first_path(ants, paths, heads, i);
			if (paths != heads->paths_head && paths->path_usage_times > 0)
				give_rest_paths(ants, paths, i, heads);
			while (paths->path_usage_times == 0 && i < data->number_of_paths)
			{
				if (paths->next == NULL)
					paths = heads->paths_head;
				else
					paths = paths->next;
			}
		}
	}
}

void	ant_mover(t_paths *paths, t_queue *queue, t_heads *heads, t_data *data)
{
	t_ants		*ants;
	t_ants		*temp;

	while (data->ant_num < data->ant_count)
		ants = make_ants(data, ants, heads);
	temp = heads->ants_head;
	ants = temp;
	give_ants_paths(ants, paths, data, heads);
	printer(ants, heads, paths, data);
}
