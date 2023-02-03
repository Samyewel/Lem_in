/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:19:17 by egaliber          #+#    #+#             */
/*   Updated: 2023/02/02 18:02:45 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
//#include "includes/lem_in.h"

void	give_rest_paths(t_ants *ants, t_paths *paths, t_data *data)
{
	ants->room = paths->path;
	paths->usage_times--;
	paths->temp++;
	if (paths->usage_times == 0)
		data->counter++;
}

void	first_move(t_ants *ants, t_paths *paths, t_data *data)
{	
	while (data->counter < data->solution->path_count \
			&& ants->has_moved == false && ants->has_finished == false)
	{
		ants->room = ants->room->next;
		send_ants(ants, data, paths);
		if (ants->next != NULL)
		{
			if (ants->room_location != ants->next->room_location)
				ants = ants->next;
		}
		if (paths->temp == 0)
		{
			data->solution->path_count--;
			data->counter--;
		}
		if (paths->next != NULL)
			paths = paths->next;
		else
			paths = data->solution->paths;
		data->counter++;
	}
}

void	move_played(t_ants *ants, t_data *data, t_heads *heads)
{
	while (ants->has_moved == true && data->finished != data->ant_count)
	{
		if (ants->has_finished == false)
		{
			move_ants_already_in_play(ants);
			if (ants->room == NULL)
			{
				ants->has_finished = true;
				data->finished++;
			}
			if (ants->next != NULL)
				ants = ants->next;
			else
			{
				ants = heads->ants;
				ft_printf("\n");
			}
		}
		else if (ants->ant_number == data->ant_count)
			ants = heads->ants;
		else
			ants = ants->next;
	}
}

void	move_ants_already_in_play(t_ants *ants)
{
	if (ants->room != NULL)
	{
		ants->room_location = ants->room->name;
		ants->room = ants->room->next;
		//ft_printf("L%d-%s ", ants->ant_number, ants->room_location);
		write(1, "L", 1);
		ft_putnbr(ants->ant_number);
		write(1, "-", 1);
		ft_putstr(ants->room_rocation);
		write(1, " ", 1);
		
	}
}

void	send_ants(t_ants *ants, t_data *data, t_paths *paths)
{
	if (data)
		ft_printf("");
	ants->room_location = ants->room->name;
	ants->room = ants->room->next;
	//ft_printf("L%d-%s ", ants->ant_number, ants->room_location);
	write(1, "L", 1);
	ft_putnbr(ants->ant_number);
	write(1, "-", 1);
	ft_putstr(ants->room_rocation);
	write(1, " ", 1);
	ants->has_moved = true;
	paths->temp--;
}
