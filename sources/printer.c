/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:16:43 by egaliber          #+#    #+#             */
/*   Updated: 2023/02/03 16:58:15 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "includes/lem_in.h"
#include "lem_in.h"

void	give_first_path(t_ants *ants, t_paths *paths, t_data *data)
{
	ants->room = paths->path;
	if (ants->next != NULL)
		ants = ants->next;
	paths->usage_times--;
	paths->temp++;
	if (paths->usage_times == 0)
		data->counter++;
}

void	printer(t_heads *heads, t_data *data)
{
	t_paths	*paths;
	t_ants	*ants;

	ants = heads->ants;
	while (data->finished != data->ant_count)
	{
		data->counter = 0;
		paths = data->solution->paths;
		first_move(ants, paths, data);
		ft_printf("\n");
		data->line_count++;
		if (heads->ants->has_moved == true)
		{
			ants = heads->ants;
			move_played(ants, data, heads);
			while (ants->has_moved == true && data->finished != data->ant_count)
			{
				if (ants->next != NULL)
					ants = ants->next;
			}
		}
	}
}

void	give_ants_paths(t_ants *ants, t_data *data, \
						t_heads *heads)
{
	t_paths	*paths;

	paths = data->solution->paths;
	ants = heads->ants;
	while (data->counter < data->solution->path_count)
	{
		paths = data->solution->paths;
		while (paths != NULL && paths->usage_times > 0)
		{
			give_rest_paths(ants, paths, data);
			paths = paths->next;
			if (ants->next != NULL)
				ants = ants->next;
		}
	}
}

void	ant_mover(t_heads *heads, t_data *data)
{
	t_ants		*ants;
	t_ants		*temp;

	while (data->ant_num < data->ant_count)
		ants = make_ants(data, ants, heads);
	temp = heads->ants;
	ants = temp;
	give_ants_paths(ants, data, heads);
	printer(heads, data);
}
