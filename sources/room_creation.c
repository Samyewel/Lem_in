/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:53:38 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/21 18:21:40 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** room_check:
** - Checks if name already exists in the list of rooms.
*/

static int	room_check(t_rooms **rooms, char *name)
{
	int	i;

	i = 0;
	if (rooms == NULL)
		return (0);
	while (++i < MAX_SIZE && rooms[i])
	{
		if (ft_strequ(name, rooms[i]->name))
			return (1);
	}
	return (0);
}

/*
** create_room:
** - Initialises a fresh room node.
*/

t_rooms	*create_room(
	t_data *data,
	t_heads *heads,
	t_rooms *room,
	char *line)
{
	room = (t_rooms *)malloc(sizeof(t_rooms));
	if (!room)
		return (NULL);
	room->id = 0;
	room->name = NULL;
	room->start = false;
	room->end = false;
	room->is_room = 0;
	room->ants = 0;
	room->x = 0;
	room->y = 0;
	room->next = NULL;
	room->links = NULL;
	store_room(data, heads, room, line);
	return (room);
}

/*
** store_room:
** - Stores the relevant data necessary to know a room's name and location, and
**   whether it is a starting or ending point for the map.
*/

t_rooms	*store_room(t_data *data, t_heads *heads, t_rooms *room, char *line)
{
	char		**line_split;

	line_split = ft_strsplit(line, ' ');
	room_store_errors(line_split);
	if (heads->room != NULL && room_check(heads->room, line_split[0]))
		clean_lem_in("Duplicate rooms.");
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
