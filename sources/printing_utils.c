/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:19:17 by egaliber          #+#    #+#             */
/*   Updated: 2023/02/09 19:50:48 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	give_rest_paths(t_ants *ants, t_paths **paths, t_data *data, int i)
{
	ants->room = paths[i]->room;
	ants->index_end = paths[i]->length;
	paths[i]->usage--;
	paths[i]->temp++;
	if (paths[i]->usage == 0)
		data->counter++;
}

void	first_move(t_ants *ants, t_paths **paths, t_data *data, int i)
{
	while (data->counter < data->solution->paths_used \
			&& ants->has_moved == false && ants->has_finished == false)
	{
		ants->index++;
		send_ants(ants, data, paths, i);
		if (ants->next != NULL)
		{
			if (ants->room_location != ants->next->room_location)
				ants = ants->next;
		}
		if (paths[i]->temp == 0)
		{
			data->solution->paths_used--;
			data->counter--;
		}
		if (i < data->solution->paths_used)
			i++;
		else
			i = 0;
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
			if (ants->index == ants->index_end)
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
				data->line_count++;
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
	if (ants->index < ants->index_end)
	{
		ants->room_location = ants->room[ants->index]->name;
		ants->index++;
		write(1, "L", 1);
		ft_putnbr(ants->ant_number);
		write(1, "-", 1);
		ft_putstr(ants->room_location);
		write(1, " ", 1);
	}
}

void	send_ants(t_ants *ants, t_data *data, t_paths **paths, int i)
{
	if (data)
		ft_printf("");
	ants->room_location = ants->room[ants->index]->name;
	ants->index++;
	write(1, "L", 1);
	ft_putnbr(ants->ant_number);
	write(1, "-", 1);
	ft_putstr(ants->room_location);
	write(1, " ", 1);
	ants->has_moved = true;
	paths[i]->temp--;
}
