/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:13:08 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/10 12:41:14 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** read_ants:
** - Reads only from the first line of the input.
** - Ensure that the link only contains a number.
** - Stores the number of ants given into a struct.
*/

static void	read_ants(t_data *data, char *line, int line_n, t_heads *heads)
{
	if (line_n == 0)
	{
		if (ft_isnumber(line))
		{
			if (ft_atoi(line) <= 0 || ft_atoi(line) > MAX_ANT)
				clean_lem_in(heads, "Error in ants.");
			else
				data->ant_count = ft_atoi(line);
		}
		else
			clean_lem_in(heads, "No ant count given.");
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

static void	read_comments(t_data *data, char *line, int line_n, t_heads *heads)
{
	if (line_n == 0)
		return ;
	if (line[0] == '#' && line[1] != '#')
	{
		if (data->ending_search == true || data->starting_search == true)
			clean_lem_in(heads, "Invalid comment.");
		return ;
	}
	if (line[0] == '#' && line[1] == '#')
	{
		start_and_end_errors(data, line, heads);
		data->starting_search = (ft_strcmp(line, "##start") == 0);
		if (data->starting_search == true)
			data->start_found = true;
		data->ending_search = (ft_strcmp(line, "##end") == 0);
		if (data->ending_search == true)
			data->end_found = true;
		start_and_end_verify(data, heads);
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
	t_rooms	*temp;

	room = NULL;
	temp = heads->room_list;
	if (line_n == 0 || (line[0] == 'L' || line[0] == '#'))
		return ;
	if (ft_strchr(line, ' ') == NULL && ft_strchr(line, '-') != NULL)
		return ;
	room_errors(line, data, heads);
	room = create_room();
	room = store_room(data, heads, room, line);
	if (!room)
		clean_lem_in(heads, "Memory allocation failure in read_rooms.");
	if (temp == NULL)
		heads->room_list = room;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = room;
	}
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
	line_split = NULL;
	if (ft_strchr(line, '-') == NULL)
		return ;
	if (ft_is_dash(line) > 1)
		clean_lem_in(heads, "Too many dashes.");
	line_split = ft_strsplit(line, '-');
	check_link_errors(line_split, data, heads);
	store_link(&heads->room_list, line_split[0], line_split[1], heads);
	store_link(&heads->room_list, line_split[1], line_split[0], heads);
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
	while (get_next_line(0, &line))
	{
		//ft_printf("%s\n", line);
		read_ants(data, line, line_n, heads);
		read_comments(data, line, line_n, heads);
		read_rooms(data, heads, line, line_n);
		read_links(heads, line, line_n, data);
		line_n++;
		if (line != NULL)
			ft_strdel(&line);
	}
	file_errors(heads, line_n, data);
}
