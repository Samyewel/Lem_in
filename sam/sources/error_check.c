/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:50:45 by egaliber          #+#    #+#             */
/*   Updated: 2023/02/13 15:04:19 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	start_and_end_errors(t_data *data, char *line, t_heads *heads)
{
	if (data->start_found == true && data->starting_search == true)
		clean_lem_in(heads, "Error in start/end node.");
	if (data->end_found == true)
		clean_lem_in(heads, "Error in start/end node.");
	if (ft_strlen(line) != 5 && ft_strlen(line) != 7)
		clean_lem_in(heads, "Error in start/end node.");
}

void	start_and_end_verify(t_data *data, t_heads *heads)
{
	if (data->starting_search && data->ending_search)
		clean_lem_in(heads, "Error in start/end node.");
	if (data->start_found == false && data->end_found == true)
		clean_lem_in(heads, "Error in start/end node.");
}

void	room_errors(char *line, t_data *data, t_heads *heads)
{
	if (ft_is_space(line) != 2)
		clean_lem_in(heads, "Invalid data.");
	if (line[0] == 'L')
		clean_lem_in(heads, "Invalid room name.");
	if (ft_isascii(line[0]) && line[1] == '-' && ft_wordcount(line, ' ') == 3)
		clean_lem_in(heads, "Invalid room name.");
	if (ft_wordcount(line, ' ') != 3)
		clean_lem_in(heads, "Invalid data.");
	if (data->links_started == true)
		clean_lem_in(heads, "Invalid data.");
}

void	verify_rooms(t_heads *heads, t_data *data)
{
	int		counter;
	int		i;

	i = -1;
	counter = 0;
	while (++i < data->room_count)
	{
		if (ft_strcmp(heads->room[i]->name, heads->room[i + 1]->name) == 0)
			clean_lem_in(heads, "Duplicate room names.");
		if (heads->room[i]->start == true || heads->room[i]->end == true)
			counter++;
	}
	if (data->ending_search == true || data->starting_search)
		clean_lem_in(heads, "No start found.");
}

void	file_errors(t_heads *heads, int line_n, t_data *data)
{
	if (line_n == 0)
		clean_lem_in(heads, "Empty file.");
	if (heads->room == NULL)
		clean_lem_in(heads, "Error in file.");
	if (data->links_started == false)
		clean_lem_in(heads, "No links.");
	if (data->start_found == false || data->end_found == false)
		clean_lem_in(heads, "Error in start/end node.");
}
