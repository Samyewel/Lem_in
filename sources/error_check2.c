/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:39:19 by egaliber          #+#    #+#             */
/*   Updated: 2023/02/09 16:23:12 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	room_store_errors(char **line_split, t_heads *heads)
{
	if (!line_split)
		clean_lem_in(heads, "Memory allocation failure in store_room_data!");
	if (!ft_isnumber(line_split[1]) || !ft_isnumber(line_split[2]))
		clean_lem_in(heads, "Coordinates given are not numbers!");
}

void	check_link_errors(char **line_split, t_data *data, t_heads *heads)
{
	if (!line_split)
		clean_lem_in(heads, "Memory allocation failure in read_links!");
	if (data->ending_search == true)
		clean_lem_in(heads, "Error in start/end!");
	// if (data->last_link_0 == line_split[0] && data->last_link_1 == line_split[1])
	// {
	// 	ft_putstr("Duplicate links!1!");
	// 	exit(1);
	// }
}
