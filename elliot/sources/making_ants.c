/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   making_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:29:46 by egaliber          #+#    #+#             */
/*   Updated: 2023/01/05 15:00:22 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/* need to add to data:
ant_num
finished
number of rooms?
-----
heads needs:
struct ants	*ants_head
*/
typedef struct s_ants
{
	struct s_queue			*next_room;
	int						ant_number;
	struct	s_ants			*next;
	char					*room_location;
	bool					has_moved;
	bool					has_finished;
}	t_ants;

void	init_ants(t_ants *new)
{
	new->ant_number = 0;
	new->next = NULL;
	new->next_room = NULL;
	new->room_location = NULL;
	new->has_moved = false;
	new->has_finished = false;
}

t_ants	*make_new_ant(t_data *data, t_ants *new)
{
	new = (t_ants *)malloc(sizeof(t_ants));
	init_ants(new);
	data->ant_num++;
	new->ant_number = data->ant_num;
	return (new);
}

t_ants	*make_ants(t_data *data, t_ants *ants, t_heads *heads)
{
	t_ants	*new_ant;
	
	new_ant = make_new_ant(data, new_ant);
	if (heads->head_ants == NULL)
	{
		ants = new_ant;
		heads->ants_head = new_ant;
	}
	else
	{
		ants->next = new_ant;
		ants = ants->next;
	}
	return (ants);
}