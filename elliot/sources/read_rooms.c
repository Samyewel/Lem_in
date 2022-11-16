/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:29:58 by egaliber          #+#    #+#             */
/*   Updated: 2022/11/16 13:22:23 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	handle_comments(t_rooms *rooms, char *line)
{
	char *room_data;

	room_data = NULL;
	if (line[0] == '#' && line[1] != '#') // valid comment?
		return ;
	
}

void	read_rooms(t_rooms *rooms)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line))
	{
		if (*line == '#')
			handle_comments(rooms, line);
	}
}