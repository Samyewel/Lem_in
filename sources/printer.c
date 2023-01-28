/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:16:43 by egaliber          #+#    #+#             */
/*   Updated: 2023/01/28 15:01:32 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	give_first_path(t_ants *ants, t_paths *paths, t_heads *heads, int i)
{
	ants->room = heads->paths->path;
	if (ants->next != NULL)
		ants = ants->next;
	paths->usage_times--;
	paths->temp++;
	i += (paths->usage_times == 0);
	if (paths->next != NULL)
		paths = paths->next;
}

void	printer(t_ants *ants, t_heads *heads, t_paths *paths, t_data *data)
{
	int	i;

	while (data->finished != data->ant_count)
	{
		i = 0;
		paths = heads->paths;
		ants = heads->ants;
		while (i < data->solution->path_count && ants->has_moved == false \
				&& ants->has_finished == false)
			first_move(ants, paths, data, i, heads);
		ft_printf("\n");
		if (heads->ants->has_moved == true)
		{
			ants = heads->ants;
			while (ants->has_moved == true \
					&& data->finished != data->ant_count)
				move_played(ants, data, heads);
		}
	}
}

void	give_ants_paths(t_ants *ants, t_paths *paths, t_data *data, \
						t_heads *heads)
{
	int	i;

	i = 0;
	paths = heads->paths;
	ants = heads->ants;
	while (i < data->solution->path_count)
	{
		while (paths->usage_times > 0)
		{
			if (paths == heads->paths && paths->usage_times > 0)
				give_first_path(ants, paths, heads, i);
			if (paths != heads->paths && paths->usage_times > 0)
				give_rest_paths(ants, paths, i, heads);
			while (paths->usage_times == 0 && i < data->solution->path_count)
			{
				if (paths->next == NULL)
					paths = heads->paths;
				else
					paths = paths->next;
			}
		}
	}
}

void	ant_mover(t_heads *heads, t_data *data)
{
	t_ants		*ants;
	t_ants		*temp;

	ft_printf("Printing\n");
	while (data->ant_num < data->ant_count)
		ants = make_ants(data, ants, heads);
	temp = heads->ants;
	ants = temp;
	give_ants_paths(ants, data->solution->paths, data, heads);
	printer(ants, heads, data->solution->paths, data);
}
