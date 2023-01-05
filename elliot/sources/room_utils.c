/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:53:38 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/05 14:52:54 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** find_start_room:
** - Points to the room that is identified as the start.
*/

t_rooms	*find_start_room(t_rooms **rooms)
{
	t_rooms	*temp_room;

	temp_room = *rooms;
	while (temp_room->start != true)
		temp_room = temp_room->next;
	return (temp_room);
}

/*
** find_end_room:
** - Points to the room that is identified as the end.
*/

t_rooms	*find_end_room(t_rooms **rooms)
{
	t_rooms	*temp_room;

	temp_room = *rooms;
	while (temp_room->end != true)
		temp_room = temp_room->next;
	return (temp_room);
}

/*
** find_room:
** - Points to the room that is given as a variable name.
*/

t_rooms	*find_room(t_rooms **rooms, char *link_name)
{
	t_rooms	*temp_room;

	temp_room = *rooms;
	while (ft_strcmp(temp_room->name, link_name) != 0)
		temp_room = temp_room->next;
	return (temp_room);
}
