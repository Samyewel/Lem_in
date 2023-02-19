/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:16:43 by egaliber          #+#    #+#             */
/*   Updated: 2023/02/19 18:15:28 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** ant_mover:
** -
*/

static void	ant_mover(t_heads *heads, t_data *data)
{
	t_paths	**paths;
	t_ants	*ants;
	int		i;

	ants = heads->ants;
	paths = data->solution->path;
	while (data->finished != data->ant_count)
	{
		data->counter = 0;
		i = 0;
		first_move(ants, paths, data, i);
		if (ANTS == true)
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
** -
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
			give_rest_paths(ants, paths, data, i);
			i++;
			if (ants->next != NULL)
				ants = ants->next;
		}
	}
}

/*
** printer:
** -
*/

void	printer(t_heads *heads, t_data *data)
{
	t_ants	*ants;
	t_ants	*temp;
	int		paths_used;

	paths_used = data->solution->paths_used;
	while (data->ant_num < data->ant_count)
		ants = make_ants(data, ants, heads);
	temp = heads->ants;
	ants = temp;
	give_ants_paths(ants, data, heads);
	data->solution->paths_used = paths_used;
	ant_mover(heads, data);
}
