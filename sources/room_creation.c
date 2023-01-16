/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:53:38 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/16 21:52:23 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** create_room:
** - Creates a fresh room.
*/

t_rooms	*create_room(t_rooms *room)
{
	room = (t_rooms *)malloc(sizeof(t_rooms));
	if (!room)
		ft_printf_strerror("Memory allocation failure in create_room.");
	room->id = 0;
	room->name = NULL;
	room->start = false;
	room->end = false;
	room->ants = 0;
	room->flow = 0;
	room->coord_x = 0;
	room->coord_y = 0;
	room->next = NULL;
	room->links = NULL;
	return (room);
}

/*
** store_room_data:
** - Stores the relevant data necessary to know a room's name and location, and
**   whether it is a starting or ending point for the map.
*/

t_rooms	*store_room_data(t_data *data, t_rooms *room, char *line)
{
	char		**line_split;

	line_split = ft_strsplit(line, ' ');
	if (!line_split)
		ft_printf_strerror("Memory allocation failure in store_room_data.");
	if (!ft_isnumber(line_split[1]) || !ft_isnumber(line_split[2]))
		ft_printf_strerror("Coordinates given are not numbers.");
	room->id = data->room_count;
	room->name = ft_strdup(line_split[0]);
	if (!room->name)
		ft_printf_strerror("Memory allocation failure in store_room_data.");
	room->coord_x = ft_atoi(line_split[1]);
	room->coord_y = ft_atoi(line_split[2]);
	ft_arrdel(line_split);
	room->start = data->starting_search;
	data->starting_search = false;
	room->end = data->ending_search;
	data->ending_search = false;
	room->flow += (room->start == false && room->end == false);
	return (room);
}
