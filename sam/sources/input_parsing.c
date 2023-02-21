/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:13:08 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/21 13:02:47 by egaliber         ###   ########.fr       */
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
	if (line_n == 0)
	{
		if (ft_isnumber(line))
		{
			if (ft_atoi(line) <= 0 || ft_atoi(line) > MAX_SIZE)
				clean_lem_in("Error in ants.");
			else
				data->ant_count = ft_atoi(line);
		}
		else
			clean_lem_in("No ant count given.");
	}
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
	{
		if (data->ending_search == true || data->starting_search == true)
			clean_lem_in("Invalid comment.");
		return ;
	}
	if (line[0] == '#' && line[1] == '#')
	{
		start_and_end_errors(data, line);
		data->starting_search = (ft_strcmp(line, "##start") == 0);
		if (data->starting_search == true)
			data->start_found = true;
		data->ending_search = (ft_strcmp(line, "##end") == 0);
		if (data->ending_search == true)
			data->end_found = true;
		start_and_end_verify(data);
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

static void	read_rooms(t_data *data, t_heads *heads, char *line, int line_n)
{
	t_rooms	*room;
	int		i;

	room = NULL;
	i = -1;
	if (line_n == 0 || (line[0] == 'L' || line[0] == '#'))
		return ;
	if (ft_strchr(line, ' ') == NULL && ft_strchr(line, '-') != NULL)
		return ;
	room_errors(line, data);
	if (heads->room == NULL)
	{
		heads->room = (t_rooms **)ft_memalloc(sizeof(t_rooms *) * MAX_SIZE);
		if (!heads->room)
			clean_lem_in("Memory allocation failure in read_rooms.");
	}
	room = create_room(data, heads, room, line);
	if (!room)
		clean_lem_in("Memory allocation failure in read_rooms.");
	while (++i < MAX_SIZE && heads->room[i] != NULL)
		;
	heads->room[i] = room;
	data->room_count++;
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

static void	read_links(t_heads *heads, char *line, int line_n, t_data *data)
{
	char	**line_split;

	if (line_n == 0 || line[0] == '#')
		return ;
	if (line[0] == 'L')
		clean_lem_in("Cannot use 'L' for room names.");
	line_split = NULL;
	if (ft_strchr(line, '-') == NULL)
		return ;
	if (ft_charcount(line, '-') > 1)
		clean_lem_in("Too many dashes.");
	line_split = ft_strsplit(line, '-');
	check_link_errors(line_split, data);
	store_link(heads->room, line_split[0], line_split[1]);
	store_link(heads->room, line_split[1], line_split[0]);
	data->links_started = true;
	data->last_link_0 = line_split[0];
	data->last_link_1 = line_split[1];
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

void	read_input(t_data *data, t_heads *heads)
{
	char	*line;
	int		line_n;

	line = NULL;
	line_n = 0;
	while (get_next_line(0, &line) > 0)
	{
		store_input(data, line, line_n);
		read_ants(data, line, line_n);
		read_comments(data, line, line_n);
		read_rooms(data, heads, line, line_n);
		read_links(heads, line, line_n, data);
		line_n++;
		if (line != NULL)
			ft_strdel(&line);
	}
	file_errors(heads, line_n, data);
	print_input(heads, data);
}
