/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:19:17 by egaliber          #+#    #+#             */
/*   Updated: 2023/02/22 14:50:36 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** all_checked:
** - If ants have reached the last we roatate back to the first.
*/

t_ants	*all_checked(t_data *data, t_ants *ants, t_heads *heads)
{
	ants = heads->ants;
	if (heads->flags->ants == true)
		ft_printf("\n");
	data->line_count++;
	return (ants);
}

/*
** first_move:
** - We send ant that arent in play to the first rooms.
**   Index is increased because start is not printed.
**   Counter is to indicate how many ants we send each turn.
** - Once we moved the same amout of ants as paths
**   the correct number has started.
*/

void	first_move(t_heads *heads, t_ants *ants, t_paths **paths, int i)
{
	while (heads->data->counter < heads->data->solution->paths_used \
			&& ants->has_moved == false && ants->has_finished == false)
	{
		ants->index++;
		send_ants(heads, ants, paths, i);
		if (ants->next != NULL)
		{
			if (ants->room_location != ants->next->room_location)
				ants = ants->next;
		}
		if (paths[i]->temp == 0)
		{
			heads->data->solution->paths_used--;
			heads->data->counter--;
		}
		if (i < heads->data->solution->paths_used)
			i++;
		else
			i = 0;
		heads->data->counter++;
	}
}

/*
** move_played:
** - We start moving ants that have already been put into play.
**   If an ant hasnt finished it needs to move.
** - Once an ant reaches to the end we activate bool finished.
**   When we've gone through all ants we print a newline.
*/

void	move_played(t_ants *ants, t_data *data, t_heads *heads)
{
	while (ants->has_moved == true && data->finished != data->ant_count)
	{
		if (ants->has_finished == false)
		{
			move_ants_already_in_play(heads, ants);
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
				if (heads->flags->ants == true)
					ft_printf("\n");
				data->line_count++;
			}
		}
		else if (ants->ant_number == data->ant_count)
			ants = all_checked(data, ants, heads);
		else
			ants = ants->next;
	}
}

/*
** move_ants_already_in_play:
** - By using the index we calculate where the ant is currently.
**   And then print its move.
*/

void	move_ants_already_in_play(t_heads *heads, t_ants *ants)
{
	if (ants->index < ants->index_end)
	{
		ants->room_location = ants->room[ants->index]->name;
		ants->index++;
		if (heads->flags->ants == true)
		{
			write(1, "L", 1);
			ft_putnbr(ants->ant_number);
			write(1, "-", 1);
			ft_putstr(ants->room_location);
			write(1, " ", 1);
		}
	}
}

/*
** send_ants:
** - By using the index we calculate where the ant is currently.
**   We then print the ants move and activate the bool moved.
**   The paths temp (usage) is decreased to
**   follow how many times a path needs to be used.
*/

void	send_ants(t_heads *heads, t_ants *ants, t_paths **paths, int i)
{
	ants->room_location = ants->room[ants->index]->name;
	ants->index++;
	if (heads->flags->ants == true)
	{
		write(1, "L", 1);
		ft_putnbr(ants->ant_number);
		write(1, "-", 1);
		ft_putstr(ants->room_location);
		write(1, " ", 1);
	}
	ants->has_moved = true;
	paths[i]->temp--;
}
