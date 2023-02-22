/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:16:43 by egaliber          #+#    #+#             */
/*   Updated: 2023/02/22 14:55:31 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** give_rest_paths:
** - Each ant is assigned with the current path and the start room.
** - Paths usage is decreased when to an ant and temp is is uage for later.
**   When usage hits 0 we decrease the amount of paths used.
*/

void	give_rest_paths(t_ants *ants, t_paths **paths, int i)
{
	ants->room = paths[i]->room;
	ants->index_end = paths[i]->length;
	paths[i]->usage--;
	paths[i]->temp++;
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
		first_move(heads, ants, paths, data->counter);
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

static void	give_ants_paths(t_ants *ants, t_data *data)
{
	int		i;
	int		x;
	int		path_count;

	path_count = data->solution->paths_used;
	i = 1;
	while (i <= data->ant_count)
	{
		if (data->solution->path[path_count - 1]->usage == 0)
			path_count--;
		x = -1;
		while (++x < path_count)
		{
			if (data->solution->path[x]->usage > 0)
			{
				give_rest_paths(ants, data->solution->path, x);
				if (ants->next != NULL)
					ants = ants->next;
				i++;
			}
			else
				break ;
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
	int		i;

	i = 0;
	print_solution(heads, data->solution);
	while (data->ant_num < data->ant_count)
		ants = make_ants(data, ants, heads);
	temp = heads->ants;
	ants = temp;
	give_ants_paths(ants, data);
	if (ants->room[i + 1]->end == true)
		only_start_end(heads, ants);
	else
		ant_mover(heads, data);
}
