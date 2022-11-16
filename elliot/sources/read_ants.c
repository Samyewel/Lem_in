/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:22:40 by egaliber          #+#    #+#             */
/*   Updated: 2022/11/16 12:27:16 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void read_ants(t_data *data)
{
	char *line;
	int ant_count;
	int i;
	
	ant_count = 0;
	line = NULL;
	i = 0;
	
	get_next_line(0, &line);
	while (line != '\0')
	{
		if (!line)
			error_management();
		if (line[i] == '0' && line[i] == '-')
			error_management();
		if (line[i] <= 47 && line[i] >= 58)
			error_management();
		i++;
	}
	ant_count = ft_atoi(line);
	data->ant_count = ant_count;
}