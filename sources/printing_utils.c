/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:19:17 by egaliber          #+#    #+#             */
/*   Updated: 2023/01/28 14:27:54 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	give_rest_paths(t_ants *ants, t_paths *paths, int i, t_heads *heads)
{
	ants->room = heads->paths->path;
	if (ants->next != NULL)
		ants = ants->next;
	paths->usage_times--;
	paths->temp++;
	if (paths->usage_times == 0)
		i++;
	if (paths->next == NULL)
		paths = heads->paths;
	else
		paths = paths->next;
}

void	first_move(t_ants *ants, t_paths *paths, t_data *data, int i, \
					t_heads *heads)
{
	send_ants(ants, data, paths);
	if (ants->next != NULL)
	{
		if (ants->room_location != ants->next->room_location)
			ants = ants->next;
	}
	if (paths->temp == 0)
	{
		data->solution->path_count--;
		i--;
	}
	if (paths->next != NULL)
		paths = paths->next;
	else
		paths = heads->paths;
	i++;
}

void	move_played(t_ants *ants, t_data *data, t_heads *heads)
{
	if (ants->has_moved == true && ants->has_finished == false)
	{
		move_ants_already_in_play(ants);
		if (ants->room == NULL)
		{
			ants->has_finished = true;
			data->finished++;
		}
		if (ants->ant_number == data->ant_count)
		{
			ants = heads->ants;
			ft_printf("\n");
		}
		else
			ants = ants->next;
	}
	else
		if (ants->ant_number == data->ant_count)
			ants = heads->ants;
	else
		ants = ants->next;
}

void	move_ants_already_in_play(t_ants *ants)
{
	while (ants->room != NULL)
	{
		ants->room_location = ants->room->name;
		ants->room = ants->room->next;
		ft_printf("L%d-%s ", ants->ant_number, ants->room_location);
		break ;
	}
}

void	send_ants(t_ants *ants, t_data *data, t_paths *paths)
{
	if (data)
		ft_printf("");
	ants->room_location = ants->room->name;
	ants->room = ants->room->next;
	ft_printf("L%d-%s ", ants->ant_number, ants->room_location);
	ants->has_moved = true;
	paths->temp--;
}
