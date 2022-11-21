/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:13:08 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/21 17:18:28 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** read_ants:
** - Reads only from the first line of the input.
** - Loops through the line, checking that only numbers are found.
** - If the line only contains a number, this will be stored.
*/

static void	read_ants(t_data *data, char *line, int line_n)
{
	if (line_n == 0 && ft_isnumber(line))
		data->ant_count = ft_atoi(line);
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

static void	read_comments(t_data *data, char *line, int line_n)
{
	int	i;

	i = 0;
	if (line_n == 0)
		return ;
	if (line[0] == '#' && line[1] != '#')
		return ;
	if (line[0] == '#' && line[1] == '#')
	{
		data->starting_search = (ft_strcmp(line, "##start") == 0);
		data->ending_search = (ft_strcmp(line, "##end") == 0);
		if (data->starting_search && data->ending_search)
		{
			ft_printf("Start and end toggles both true in %s on line %d.\n", __func__, __LINE__);
			exit(EXIT_FAILURE);
		}
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
			ft_printf_strerror("Invalid input.");
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
** -
*/

static void	read_links(t_links *links, char *line, int line_n)
{
	char	**link_split;
	int		i;

	link_split = NULL;
	i = 0;
	if (line_n > 0)
	{
		if (ft_strchr(line, '-') != NULL && ft_strchr(line, ' ') == NULL)
			return ;
		link_split = ft_strsplit(line, '-');
		if (!link_split)
		{
			ft_printf("Memory allocation failure in %s on line %d.\n", __func__, __LINE__);
			exit(EXIT_FAILURE);
		}
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

void	read_input(t_data *data, t_rooms **rooms, t_links *links)
{
	char	*line;
	int		line_n;

	line = NULL;
	line_n = 0;
	while (get_next_line(0, &line))
	{
		ft_printf("%s\n", line);
		read_ants(data, line, line_n);
		read_comments(data, line, line_n);
		read_rooms(data, rooms, line, line_n);
		read_links(links, line, line_n);
		line_n++;
		if (line != NULL)
			ft_strdel(&line);
	}
}
