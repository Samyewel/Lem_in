/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:16:43 by egaliber          #+#    #+#             */
/*   Updated: 2023/02/20 14:29:08 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** give_rest_paths:
** - Each ant is assigned with the current path and the start room.
** - Paths usage is decreased when to an ant and temp is is uage for later.
**   When usage hits 0 we decrease the amount of paths used.
*/

void	give_rest_paths(t_ants *ants, t_paths **paths, t_data *data, int i)
{
	ants->room = paths[i]->room;
	ants->index_end = paths[i]->length;
	paths[i]->usage--;
	paths[i]->temp++;
	if (paths[i]->usage == 0)
		data->solution->paths_used--;
}

/*
** only_start_end:
** - Small function that takes of cases where there is only start-end.
**   Prints all ants on the same line.
*/

void	only_start_end(t_heads *heads, t_ants *ants)
{
	while (ants)
	{
		ants->room_location = ants->room[1]->name;
		if (heads->flags->ants == true)
		{
			write(1, "L", 1);
			ft_putnbr(ants->ant_number);
			write(1, "-", 1);
			ft_putstr(ants->room_location);
			write(1, " ", 1);
		}
		if (ants->next != NULL)
			ants = ants->next;
		else
			break ;
	}
	if (heads->flags->ants == true)
		ft_printf("\n");
	heads->data->line_count++;
}

/*
** ant_mover:
** - We start moving the ants untill all of them have finished.
** - First sending the ants that haven't started yet.
** - Once we see some ants are in play those are moved
**   before sending new ones.
** - When all ants that are in play have moved
**   we send the next bunch of new ants.
**   When all ants are in play and we just keep moving them.
*/

static void	ant_mover(t_heads *heads, t_data *data)
{
	t_paths	**paths;
	t_ants	*ants;

	ants = heads->ants;
	paths = data->solution->path;
	while (data->finished != data->ant_count)
	{
		data->counter = 0;
		first_move(heads, ants, paths, 0);
		if (heads->flags->ants == true)
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

/*
** give_ants_paths:
** - Each ant is assigned with a path to use depending on how many paths we use.
**   If a paths usage hits 0, we go to the next path.
** - After a path is given we move to the next path and ant
**   untill all paths are done.
*/

static void	give_ants_paths(t_ants *ants, t_data *data, t_heads *heads)
{
	t_paths	**paths;
	int		i;

	paths = data->solution->path;
	ants = heads->ants;
	while (data->solution->paths_used > 0)
	{
		i = 0;
		while (i < data->solution->paths_used)
		{
			while (paths[i]->usage == 0)
				i++;
			give_rest_paths(ants, paths, data, i);
			i++;
			if (ants->next != NULL)
				ants = ants->next;
		}
	}
}

/*
** printer:
** - The "main of the Printer".
**   First we create ant struct and make the into a list.
**   We give those ants the correct paths and rooms to start.
**   Then we start moving and print the ants.
*/

void	printer(t_heads *heads, t_data *data)
{
	t_ants	*ants;
	t_ants	*temp;
	int		paths_used;
	int		i;

	i = 0;
	paths_used = data->solution->paths_used;
	while (data->ant_num < data->ant_count)
		ants = make_ants(data, ants, heads);
	temp = heads->ants;
	ants = temp;
	give_ants_paths(ants, data, heads);
	data->solution->paths_used = paths_used;
	if (ants->room[i + 1]->end == true)
		only_start_end(heads, ants);
	else
		ant_mover(heads, data);
}
