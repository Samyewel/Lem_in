/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_done.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:16:43 by egaliber          #+#    #+#             */
/*   Updated: 2023/01/18 16:36:48 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	give_first_path(t_ants *ants, t_paths *paths, t_data *data)
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

void	printer(t_result *res, t_ants *ants, t_data *data, t_paths *paths)
{
	int i;

	while (res->finished != data->number_of_ants)
	{
		i = 0;
		paths = data->head2;
		ants = data->head_ants;
		while (i < data->number_of_paths && ants->has_moved == false \
				&& ants->has_finished == false)
			first_move(ants, paths, res, data);
		ft_printf("\n");
		if (data->head_ants->has_moved == true)
		{
			ants = data->head_ants;
			while (ants->has_moved == true && \ 
					res->finished != data->number_of_ants)
				move_played(ants, paths, res, data);
		}
	}
}

void	give_ants_paths(t_ants *ants, t_paths *paths, t_data *data)
{
	int	i;

	i = 0;
	paths = data->head2;
	ants = data->head_ants;
	while (i < data->number_of_paths)
	{
		while (paths->path_usage_times > 0)
		{
			if (paths == data->head2 && paths->path_usage_times > 0)
				give_first_path(ants, paths, data);
			if (paths != data->head2 && paths->path_usage_times > 0)
				give_rest_paths(ants, paths, data);
			while (paths->path_usage_times == 0 && i < data->number_of_paths)
			{
				if (paths->next == NULL)
					paths = data->head2;
				else
					paths = paths->next;
			}
		}
	}
}

void	ant_mover(/*t_paths *paths,*/ t_queue *queue, t_heads *heads, t_data *data)
{
	t_ants	*ants;
	t_ants	*temp;

	while (data->ant_num < data->ant_count)
		ants = make_ants(data, ants, heads);
	temp = heads->ants_head;
	ants = temp;
	give_ants_paths(ants, paths, data);
	printer(ants, queue, heads, paths, data);
}