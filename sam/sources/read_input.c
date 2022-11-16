/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:13:08 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/16 16:03:27 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** read_ants:
** - Reads only from the first line of the input.
** - Loops through the line, checking that only numbers are found.
** - If the line only contains a number, this will be stored.
*/

static void	read_ants(t_data *data, char *line, int line_count)
{
	int	i;

	i = 0;
	if (line_count == 0)
	{
		while (line[i])
		{
			if (!ft_isdigit(line[i]))
				return ;
			i++;
		}
		data->ant_count = ft_atoi(line);
	}
}

/*
** read_comments:
** - Will only be read after the first line.
** - If a line begins with one '#', it a comment for user-reading purposes, and
**   therefore will not be stored or printed.
** - If a line begins with two '#', it is a modifier for the next room to
**   specify if it is the start or end room. This triggers a boolean used for
**   searching for the next line that contains a room.
*/

static void	read_comments(t_rooms *rooms, char *line, int line_count)
{
	int	i;

	i = 0;
	if (line_count > 0)
	{
		if (line[0] == '#' && line[1] == '#')
		{
			if (ft_strcmp(line, "##start") == 0)
				rooms->start_searching = true;
			if (ft_strcmp(line, "##end") == 0)
				rooms->end_searching = true;
		}
		if (line[0] == '#' && line[1] != '#')
			return ;
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
** - If we are searching for the next room given after a start or end modifier,
**   that room is given the corresponding value.
*/

static void	read_rooms(t_rooms *rooms, char *line, int line_count)
{
	char	**room_split;
	int		i;

	room_split = NULL;
	i = 0;
	if (line_count > 0 && line[0] != 'L' && line[0] != '#')
	{
		if (ft_strchr(line, ' ') != NULL)
			return ;
		room_split = ft_strsplit(line, ' ');
		if (!room_split)
			exit(EXIT_FAILURE);
		rooms->name = room_split[0];
		rooms->coord_x = ft_atoi(room_split[1]);
		rooms->coord_y = ft_atoi(room_split[2]);
		rooms->start = rooms->start_searching;
		rooms->start_searching = false;
		rooms->end = rooms->end_searching;
		rooms->end_searching = false;
		ft_arrdel(room_split);
		rooms->next = NULL;
	}
}

/*
** read_links:
** -
*/

static void	read_links(t_links *links, char *line, int line_count)
{
	char	**link_split;
	int		i;

	link_split = NULL;
	i = 0;
	if (line_count > 0)
	{
		if (ft_strchr(line, '-') != NULL)
			return ;
		link_split = ft_strsplit(line, '-');
		if (!link_split)
			exit(EXIT_FAILURE);
		links->a = link_split[0];
		links->b = link_split[1];
		ft_arrdel(link_split);
		links->next = NULL;
	}
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

void	read_input(t_data *data, t_rooms *rooms, t_links *links)
{
	char	*line;
	int		line_count;

	line = NULL;
	line_count = 0;
	while (get_next_line(0, &line))
	{
		read_ants(data, line, line_count);
		read_comments(rooms, line, line_count);
		read_rooms(rooms, line, line_count);
		read_links(links, line, line_count);
		if (line != NULL)
			ft_strdel(&line);
	}
}
