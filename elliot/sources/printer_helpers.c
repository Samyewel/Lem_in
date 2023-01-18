/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:19:17 by egaliber          #+#    #+#             */
/*   Updated: 2023/01/18 17:15:41 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	give_rest_paths(t_ants *ants, t_paths *paths, t_data *data, int i, \
						t_heads *heads)
{
	ants->room = paths->head;
	if (ants->next != NULL)
		ants = ants->next;
	paths->path_usage_times--;
	paths->temp++;
	if (paths->path_usage_times == 0)
		i++;
	if (paths->next == NULL)
		paths = heads->paths_head;
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
		data->number_of_paths--;
		i--;
	}
	if (paths->next != NULL)
		paths = paths->next;
	else
		paths = heads->paths_head;
	i++;
}

void	move_played(t_ants *ants, t_paths *paths, t_result *res, t_data *data, \
					t_heads *heads)
{
	if (ants->has_moved == true && ants->has_finished == false)
	{
		move_ants_alrdy_in_play(res, ants, data, paths);
		if (ants->room == NULL)
		{
			ants->has_finished = true;
			res->finished++;
		}
		if (ants->ant_number == data->ant_count)
		{
			ants = heads->ants_head;
			ft_printf("\n");
		}
		else
			ants = ants->next;
	}
	else
		if (ants->ant_number == data->ant_count)
			ants = heads->ants_head;
	else
		ants = ants->next;
}

void	move_ants_alrdy_in_play(t_result *res, t_ants *ants, t_data *data, \
								t_paths *paths)
{
	while (ants->room != NULL)
	{
		ants->room_location = ft_itoa(ants->room->room);
		ants->room = ants->room->next;
		ft_printf("L%d-%s ", ants->ant_number, ants->room_location);
		break ;
	}
}

void	send_ants(t_result *res, t_ants *ants, t_data *data, t_paths *paths)
{
	ants->room_location = ft_itoa(ants->room->room);
	ants->room = ants->room->next;
	ft_printf("L%d-%s ", ants->ant_number, ants->room_location);
	ants->has_moved = true;
	paths->temp--;
}
