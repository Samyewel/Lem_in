/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:39:19 by egaliber          #+#    #+#             */
/*   Updated: 2023/02/10 12:39:11 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	room_store_errors(char **line_split, t_heads *heads)
{
	if (!line_split)
		clean_lem_in(heads, "Memory allocation failure in store_room_data.");
	if (!ft_isnumber(line_split[1]) || !ft_isnumber(line_split[2]))
		clean_lem_in(heads, "Coordinates given are not numbers.");
}

void	check_link_errors(char **line_split, t_data *data, t_heads *heads)
{
	if (!line_split)
		clean_lem_in(heads, "Memory allocation failure in read_links.");
	if (data->ending_search == true)
		clean_lem_in(heads, "Error in start/end node.");
}
