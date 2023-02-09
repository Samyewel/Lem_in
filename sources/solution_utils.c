/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:17:07 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/09 12:41:05 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_paths	*shortest_path(t_data *data, t_heads *heads)
{
	t_paths	*shortest_path;
	int		shortest_length;
	int		i;

	shortest_length = INT_MAX;
	shortest_path = 0;
	i = -1;
	while (++i < data->path_count)
	{
		if (heads->path[i]->length < shortest_length)
		{
			shortest_length = heads->path[i]->length;
			shortest_path = heads->path[i];
		}
	}
	return (shortest_path);
}

void	sort_solution(t_heads *heads, int *array)
{
	int		i;
	int		temp;
	bool	swapped;

	i = 1;
	temp = 0;
	swapped = 0;
	while (i < MAX_SIZE)
	{
		if (array[i] < 0)
			break ;
		swapped = 0;
		if (get_path(heads, array[i])->length < \
				get_path(heads, array[i - 1])->length && i > 0)
		{
			temp = array[i];
			array[i] = array[i - 1];
			array[i - 1] = temp;
			i = 1;
			swapped = 1;
		}
		if (swapped == 0)
			i++;
	}
}
