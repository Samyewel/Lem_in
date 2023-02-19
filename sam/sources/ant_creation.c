/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:29:46 by egaliber          #+#    #+#             */
/*   Updated: 2023/02/19 16:02:54 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** init_ants:
** -
*/

void	init_ants(t_ants *new)
{
	new->ant_number = 0;
	new->next = NULL;
	new->room = NULL;
	new->room_location = NULL;
	new->has_moved = false;
	new->has_finished = false;
	new->index = 0;
	new->index_end = 0;
}

/*
** make_new_ant:
** -
*/

t_ants	*make_new_ant(t_data *data, t_ants *new)
{
	new = (t_ants *)malloc(sizeof(t_ants));
	if (!new)
		return (NULL);
	init_ants(new);
	data->ant_num++;
	new->ant_number = data->ant_num;
	return (new);
}

/*
** make_ants:
** -
*/

t_ants	*make_ants(t_data *data, t_ants *ants, t_heads *heads)
{
	t_ants	*new_ant;

	new_ant = NULL;
	new_ant = make_new_ant(data, new_ant);
	if (!new_ant)
		clean_lem_in("Memory allocation failure in make_ants.");
	if (heads->ants == NULL)
	{
		ants = new_ant;
		heads->ants = new_ant;
	}
	else
	{
		ants->next = new_ant;
		ants = ants->next;
	}
	return (ants);
}
