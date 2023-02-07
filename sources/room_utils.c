/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:53:38 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/06 14:20:19 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** find_start_room:
** - Points to the room that is identified as the start.
*/

int	find_start_room(t_heads *heads)
{
	int		i;

	i = -1;
	while (++i < MAX_SIZE)
	{
		if (heads->room_array[i] == NULL)
			return (-1);
		if (heads->room_array[i]->start == true)
			return (i);
	}
	return (-1);
}

/*
** find_end_room:
** - Points to the room that is identified as the end.
*/

int		find_end_room(t_heads *heads)
{
	int		i;

	i = -1;
	while (++i < MAX_SIZE)
	{
		if (heads->room_array[i] == NULL)
			return (-1);
		if (heads->room_array[i]->end == true)
			return (i);
	}
	return (-1);
}

/*
** find_room:
** - Points to the room that is given as a variable name.
*/

t_rooms	*find_room(t_rooms **rooms, int room_id)
{
	if (room_id >= MAX_SIZE || room_id < 0 || rooms[room_id] == NULL)
		return (NULL);
	return (rooms[room_id]);
}

/*
** find_room_name:
** -
*/

t_rooms *find_room_name(t_rooms **rooms, char *name)
{
	t_rooms *temp_room;

	temp_room = *rooms;
	while (temp_room)
	{
		if (ft_strcmp(temp_room->name, name) == 0)
			return (temp_room);
		temp_room = temp_room->next;
	}
	return (NULL);
}
