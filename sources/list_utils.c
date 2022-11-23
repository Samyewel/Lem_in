/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:53:38 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/23 16:07:08 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms	*find_start_room(t_rooms **rooms)
{
	t_rooms	*temp;

	temp = *rooms;
	while (temp->start != true)
		temp = temp->next;
	return (temp);
}

t_rooms	*find_end_room(t_rooms **rooms)
{
	t_rooms	*temp;

	temp = *rooms;
	while (temp->end != true)
		temp = temp->next;
	return (temp);
}

t_rooms	*find_room(t_rooms **rooms, char *link_name)
{
	t_rooms	*room;

	room = *rooms;
	while (ft_strcmp(room->name, link_name) != 0)
		room = room->next;
	return (room);
}
