/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:53:38 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/13 15:01:29 by sam              ###   ########.fr       */
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
		if (heads->room[i] == NULL)
			return (-1);
		if (heads->room[i]->start == true)
			return (i);
	}
	return (-1);
}

/*
** find_end_room:
** - Points to the room that is identified as the end.
*/

int	find_end_room(t_heads *heads)
{
	int		i;

	i = -1;
	while (++i < MAX_SIZE)
	{
		if (heads->room[i] == NULL)
			return (-1);
		if (heads->room[i]->end == true)
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
** - Finds the room name that is equal to the given search name.
*/

t_rooms	*find_room_name(t_rooms **rooms, char *name)
{
	int	i;

	i = -1;
	while (++i < MAX_SIZE)
	{
		if (ft_strequ(name, rooms[i]->name))
			return (rooms[i]);
	}
	return (NULL);
}
