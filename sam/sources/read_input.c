/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:13:08 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/23 13:36:45 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** read_ants:
** - Reads only from the first line of the input.
** - Ensure that the link only contains a number.
** - Stores the number of ants given into a struct.
*/

static void	read_ants(t_data *data, char *line, int line_n)
{
	if (line_n == 0 && ft_isnumber(line))
		data->ant_count = ft_atoi(line);
}

/*
** read_comments:
** - Will only be read after the first line.
** - If a line begins with one '#', it's a comment for user-reading
*8   purposes, and therefore will not be stored or printed.
** - If a line begins with two '#', it's is a modifier for the next room to
**   specify if it is the start or end room. This triggers a boolean used for
**   searching for the next line that contains a room.
*/

static void	read_comments(t_data *data, char *line, int line_n)
{
	if (line_n == 0)
		return ;
	if (line[0] == '#' && line[1] != '#')
		return ;
	if (line[0] == '#' && line[1] == '#')
	{
		data->starting_search = (ft_strcmp(line, "##start") == 0);
		data->ending_search = (ft_strcmp(line, "##end") == 0);
		if (data->starting_search && data->ending_search)
			ft_printf_strerror("Start and end toggles both true.");
	}
}

/*
** read_rooms:
** - Will only be read after the first line.
** - As a room name cannot begin with 'L' (ant naming) or '#' (comment), these
**   criteria are necessary for initiating this function.
** - Searches for a ' ' to ensure that the line contains a room name and it's
**   coordinates.
** - Splits the line into three pieces of storable data (name, x coordinate,
**   y coordinates).
** - All necessary room data is then allocated and added to the list of rooms.
*/

static void	read_rooms(t_data *data, t_rooms **rooms, char *line, int line_n)
{
	t_rooms	*room;
	t_rooms	*temp;

	room = NULL;
	temp = *rooms;
	if (line_n > 0 && line[0] != 'L' && line[0] != '#')
	{
		if (ft_strchr(line, ' ') == NULL && ft_strchr(line, '-') != NULL)
			return ;
		if (ft_wordcount(line, ' ') != 3)
			ft_printf_strerror("Invalid coordinate input.");
		room = create_room(*rooms);
		room = store_room_data(data, room, line);
		if (temp == NULL)
			*rooms = room;
		else
		{
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = room;
		}
	}
}

/*
** read_links:
** - Ensures that the line met is not the first, and that it meets the criteria
**   for a valid link command.
** - Splits the line into two names, with each representing that room's between
**   one link.
** - Calls add_link twice with the names alternating, giving those rooms a link
**   between the two.
*/

static void	read_links(t_rooms **rooms, char *line, int line_n)
{
	char	**line_split;
	t_links	*link;
	t_rooms	*temp;

	line_split = NULL;
	link = NULL;
	temp = *rooms;
	if (line_n == 0)
		return ;
	if (ft_strchr(line, '-') == NULL)
		return ;
	line_split = ft_strsplit(line, '-');
	if (!line_split)
		ft_printf_strerror("Memory allocation failure in read_links.");
	add_link(rooms, line_split[0], line_split[1]);
	add_link(rooms, line_split[1], line_split[0]);
	ft_arrdel(line_split);
}

/*
** read_input:
** - Loops through the given input file, reading each line depending when it's
**   criteria is met.
** - read_ants will only read the first line.
** - read_comments will only read lines containing '#' symbols.
** - read_rooms will only read lines containing ' ' symbols.
** - read_links will only read lines containing '-' symbols.
*/

void	read_input(t_data *data, t_rooms **rooms)
{
	char	*line;
	int		line_n;

	line = NULL;
	line_n = 0;
	while (get_next_line(0, &line))
	{
		ft_printf("%s\n", line); //Remove before submission
		read_ants(data, line, line_n);
		read_comments(data, line, line_n);
		read_rooms(data, rooms, line, line_n);
		read_links(rooms, line, line_n);
		line_n++;
		if (line != NULL)
			ft_strdel(&line);
	}
}
