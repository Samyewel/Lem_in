/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:53:38 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/09 16:07:08 by egaliber         ###   ########.fr       */
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

t_rooms	*create_room(t_rooms *room)
{
	room = (t_rooms *)malloc(sizeof(t_rooms));
	if (!room)
		ft_printf_strerror("Memory allocation failure in create_room.");
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
	return (room);
}

/*
** store_room_data:
** - Stores the relevant data necessary to know a room's name and location, and
**   whether it is a starting or ending point for the map.
*/

t_rooms	*store_room_data(t_data *data, t_rooms *room, char *line, t_heads *heads)
{
	char		**line_split;

	line_split = ft_strsplit(line, ' ');
	room->id = data->room_count;
	room_store_errors(line_split, heads);
	if (heads)
		ft_printf("");
	if (room_check(heads->room_list, line_split[0]))
	{
		ft_putstr("Duplicate rooms!!");
		exit(1);
	}
	room->name = ft_strdup(line_split[0]);
	if (!room->name)
	{
		ft_putstr("Memory allocation failure in store_room_data.");
		exit(1);
	}
	room->x = ft_atoi(line_split[1]);
	room->y = ft_atoi(line_split[2]);
	ft_arrdel(line_split);
	room->start = data->starting_search;
	data->starting_search = false;
	room->end = data->ending_search;
	data->ending_search = false;
	return (room);
}
