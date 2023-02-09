/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:50:45 by egaliber          #+#    #+#             */
/*   Updated: 2023/02/09 19:53:59 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	start_and_end_errors(t_data *data, char *line, t_heads *heads)
{
	if (data->start_found == true && data->starting_search == true)
		clean_lem_in(heads, "Error in start/end!");
	if (data->end_found == true)
		clean_lem_in(heads, "Error in start/end!");
	if (ft_strlen(line) != 5 && ft_strlen(line) != 7)
		clean_lem_in(heads, "Error in start/end!");
}

void	start_and_end_verify(t_data *data, t_heads *heads)
{
	if (data->starting_search && data->ending_search)
		clean_lem_in(heads, "Error in start/end!");
	if (data->start_found == false && data->end_found == true)
		clean_lem_in(heads, "Error in start/end!");
}

void	room_errors(char *line, t_data *data, t_heads *heads)
{
	if (ft_is_space(line) != 2)
		clean_lem_in(heads, "Invalid Data!");
	if (line[0] == 'L')
		clean_lem_in(heads, "Invalid Room name!");
	if (ft_isascii(line[0]) && line[1] == '-' && ft_wordcount(line, ' ') == 3)
		clean_lem_in(heads, "Invalid Room name!");
	if (ft_wordcount(line, ' ') != 3)
		clean_lem_in(heads, "Invalid Data!");
	if (data->links_started == true)
		clean_lem_in(heads, "Invalid Data!");
}

void	verify_rooms(t_heads *heads, t_data *data)
{
	t_rooms	**temp;
	int		counter;
	int		i;

	i = 0;
	counter = 0;
	temp = heads->room;
	while (i < data->room_count)
	{
		if (ft_strcmp(temp[i]->name, temp[i + 1]->name) == 0)
			clean_lem_in(heads, "Duplicate Room Names!");
		if (temp[i]->start == true || temp[i]->end == true)
			counter++;
		i++;
	}
	if (data->ending_search == true || data->starting_search)
		clean_lem_in(heads, "No Start found!");
}

void	file_errors(t_heads *heads, int line_n, t_data *data)
{
	if (line_n == 0)
		clean_lem_in(heads, "Empty File!");
	if (heads->room_list == NULL)
		clean_lem_in(heads, "Error in File!");
	if (data->links_started == false)
		clean_lem_in(heads, "No Links!");
	if (data->start_found == false || data->end_found == false)
		clean_lem_in(heads, "Error in start/end!");
}
