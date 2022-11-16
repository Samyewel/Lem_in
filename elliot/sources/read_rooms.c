/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:29:58 by egaliber          #+#    #+#             */
/*   Updated: 2022/11/16 12:46:50 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	read_rooms(t_rooms *rooms)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line))
	{
		if (line == '#')
			handle_comments()
	}
}