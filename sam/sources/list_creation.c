/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:33:57 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/23 16:03:24 by swilliam         ###   ########.fr       */
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
		ft_printf("Memory allocation failure in create_room.");
	room->name = NULL;
	room->coord_x = 0;
	room->coord_y = 0;
	room->start = 0;
	room->end = 0;
	room->ants = 0;
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
	char	**line_split;

	line_split = ft_strsplit(line, ' ');
	if (!line_split)
		ft_printf_strerror("Memory allocation failure in store_room_data.");
	if (!ft_isnumber(line_split[1]) || !ft_isnumber(line_split[2]))
		ft_printf_strerror("Coordinates given are not numbers.");
	room->name = ft_strdup(line_split[0]);
	room->coord_x = ft_atoi(line_split[1]);
	room->coord_y = ft_atoi(line_split[2]);
	ft_arrdel(line_split);
	room->start = data->starting_search;
	data->starting_search = false;
	room->end = data->ending_search;
	data->ending_search = false;
	return (room);
}

/*
** create_link:
** - Creates a fresh link to be added to a list.
** - Takes the name of a linked room and modifies the link's name.
*/

static t_links	*create_link(char *link_name)
{
	t_links	*link;

	link = (t_links *)malloc(sizeof(t_rooms));
	if (!link)
		ft_printf("Memory allocation failure in create_link.");
	link->name = ft_strdup(link_name);
	if (!link->name)
		ft_printf("Memory allocation failure in create_link.");
	link->next = NULL;
	return (link);
}

/*
** add_link:
** - Creates a linked list containing each neigbouring room that a room
**   links to.
*/

t_links	*add_link(t_rooms **rooms, char *link_a, char *link_b)
{
	t_links	*link;
	t_rooms	*temp_room;
	t_links	*temp_link;

	link = NULL;
	link = create_link(link_b);
	temp_link = NULL;
	temp_room = find_room(rooms, link_a);
	if (temp_room->links == NULL)
		temp_room->links = link;
	else
	{
		temp_link = temp_room->links;
		while (temp_link->next != NULL)
			temp_link = temp_link->next;
		temp_link->next = link;
	}
	return (link);
}
