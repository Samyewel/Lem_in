/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_errors_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:39:19 by egaliber          #+#    #+#             */
/*   Updated: 2023/02/19 16:48:09 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	room_store_errors(char **line_split)
{
	if (!line_split)
		clean_lem_in("Memory allocation failure in store_room_data.");
	if (!ft_isnumber(line_split[1]) || !ft_isnumber(line_split[2]))
		clean_lem_in("Coordinates given are not numbers.");
}

void	check_link_errors(char **line_split, t_data *data)
{
	if (!line_split)
		clean_lem_in("Memory allocation failure in read_links.");
	if (data->ending_search == true)
		clean_lem_in("Error in start/end node.");
}

void	room_errors(char *line, t_data *data)
{
	if (ft_charcount(line, ' ') != 2)
		clean_lem_in("Invalid data.");
	if (line[0] == 'L')
		clean_lem_in("Invalid room name.");
	if (ft_isascii(line[0]) && line[1] == '-' && ft_wordcount(line, ' ') == 3)
		clean_lem_in("Invalid room name.");
	if (ft_wordcount(line, ' ') != 3)
		clean_lem_in("Invalid data.");
	if (data->links_started == true)
		clean_lem_in("Invalid data.");
}
