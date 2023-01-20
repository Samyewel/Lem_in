/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_done.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:16:43 by egaliber          #+#    #+#             */
/*   Updated: 2023/01/18 17:19:21 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
	Need to sort:
	where we init res
	does paths have a head that points to first room
	paths_usage_time
	paths need a temp
	change res to be in data?
*/

typedef struct s_result
{
	int		finished;
	int		ant_number;
}	t_result;

void	give_first_path(t_ants *ants, t_paths *paths, int i)
{
	ants->room = paths->head;
	if (ants->next != NULL)
		ants = ants->next;
	paths->path_usage_times--;
	paths->temp++;
	if (paths->path_usage_times == 0)
		i++;
	if (paths->next != NULL)
		paths = paths->next;
}

void	printer(t_ants *ants, t_heads *heads, t_paths *paths, t_data *data, \
				t_result *res)
{
	int	i;

	while (res->finished != data->ant_count)
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
					&& res->finished != data->ant_count)
				move_played(ants, paths, res, data, heads);
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
				give_first_path(ants, paths, i);
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

void	init_res(t_result *res)
{
	res->ant_number = 0;
	res->finished = 0;
}

void	ant_mover(t_paths *paths, t_queue *queue, t_heads *heads, t_data *data)
{
	t_ants		*ants;
	t_ants		*temp;
	t_result	*res;

	while (data->ant_num < data->ant_count)
		ants = make_ants(data, ants, heads);
	temp = heads->ants_head;
	ants = temp;
	init_res(res);
	give_ants_paths(ants, paths, data, heads);
	printer(ants, heads, paths, data, res);
}
