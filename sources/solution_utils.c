/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:17:07 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/03 18:34:43 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_paths	*find_shortest_path(t_heads *heads)
{
	t_paths	*temp_path;
	t_paths	*shortest_path;
	int		shortest_length;

	temp_path = heads->paths;
	shortest_length = INT_MAX;
	shortest_path = 0;
	while (temp_path)
	{
		if (temp_path->length < shortest_length)
		{
			shortest_length = temp_path->length;
			shortest_path = temp_path;
		}
		temp_path = temp_path->next;
	}
	return (shortest_path);
}

void	sort_solution_array(t_heads *heads, int *array)
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
