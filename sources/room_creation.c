/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:53:38 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/09 20:24:05 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** create_room:
** - Creates a fresh room.
*/

int	room_check(t_rooms *head, char *name)
{
	t_rooms	*room;

	room = head;
	while (room)
	{
		if (ft_strequ(room->name, name))
			return (1);
		room = room->next;
	}
	return (0);
}

t_rooms	*create_room(void)
{
	t_rooms	*new_room;

	new_room = NULL;
	new_room = (t_rooms *)malloc(sizeof(t_rooms));
	if (!new_room)
		return (NULL);
	new_room->id = 0;
	new_room->name = NULL;
	new_room->start = false;
	new_room->end = false;
	new_room->is_room = 0;
	new_room->ants = 0;
	new_room->x = 0;
	new_room->y = 0;
	new_room->next = NULL;
	new_room->links = NULL;
	return (new_room);
}

/*
** store_room_data:
** - Stores the relevant data necessary to know a room's name and location, and
**   whether it is a starting or ending point for the map.
*/

t_rooms	*store_room(t_data *data, t_heads *heads, t_rooms *room, char *line)
{
	char		**line_split;

	line_split = ft_strsplit(line, ' ');
	room_store_errors(line_split, heads);
	if (room_check(heads->room_list, line_split[0]))
		clean_lem_in(heads, "Duplicate rooms.");
	room->id = data->room_count;
	room->name = ft_strdup(line_split[0]);
	if (!room->name)
		return (NULL);
	room->x = ft_atoi(line_split[1]);
	room->y = ft_atoi(line_split[2]);
	ft_arrdel(line_split);
	room->start = data->starting_search;
	data->starting_search = false;
	room->end = data->ending_search;
	data->ending_search = false;
	return (room);
}
