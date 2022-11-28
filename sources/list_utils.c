/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:53:38 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/28 21:23:00 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** find_start_room:
** - Points to the room that is identified as the start.
*/

t_rooms	*find_start_room(t_rooms **rooms)
{
	t_rooms	*temp;

	temp = *rooms;
	while (temp->start != true)
		temp = temp->next;
	return (temp);
}

/*
** find_end_room:
** - Points to the room that is identified as the end.
*/

t_rooms	*find_end_room(t_rooms **rooms)
{
	t_rooms	*temp;

	temp = *rooms;
	while (temp->end != true)
		temp = temp->next;
	return (temp);
}

/*
** find_room:
** - Points to the room that is given as a variable name.
*/

t_rooms	*find_room(t_rooms **rooms, char *link_name)
{
	t_rooms	*room;

	room = *rooms;
	while (ft_strcmp(room->name, link_name) != 0)
		room = room->next;
	return (room);
}
