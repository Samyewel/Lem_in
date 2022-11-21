/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:27:53 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/21 17:13:30 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms	*store_room_data(t_data *data, t_rooms *room, char *line)
{
	char	**line_split;

	line_split = ft_strsplit(line, ' ');
	if (!line_split)
	{
		ft_printf("Memory allocation failure in %s on line %d.", __func__, __LINE__);
		exit(EXIT_FAILURE);
	}
	if (!ft_isnumber(line_split[1]) || !ft_isnumber(line_split[2]))
	{
		ft_printf_strerror("Coordinates given are not numbers.");
		exit(EXIT_FAILURE);
	}
	room->name = ft_strdup(line_split[0]);
	room->coord_x = ft_atoi(line_split[1]);
	room->coord_y = ft_atoi(line_split[2]);
	room->start = data->starting_search;
	data->starting_search = false;
	room->end = data->ending_search;
	data->ending_search = false;
	ft_arrdel(line_split);
	return (room);
}
