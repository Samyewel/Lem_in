/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:17:07 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/09 15:27:03 by swilliam         ###   ########.fr       */
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

static int	test_round(t_data *data)
{
	int	most_moves;
	int	i;

	i = -1;
	most_moves = 0;
	while (++i < data->solution->path_count)
	{
		if (data->solution->path[i]->temp_usage > 0)
		{
			if (data->solution->path[i]->length + data->solution->path[i]->temp_usage > most_moves)
				most_moves = data->solution->path[i]->length + data->solution->path[i]->temp_usage;
		}

	}
	return (most_moves);
}

void	calculate_usage_times(t_data *data)
{
	int	i;
	int	best;
	int	moves;

	i = -1;
	moves = 0;
	best = INT_MAX;
	data->solution->path[0]->temp_usage = data->ant_count;
	if (data->solution->path_count > 1)
	{
		i = -1;
		while (++i < data->ant_count)
		{
			moves = test_round(data);
			if (moves > 0 && moves < best)
			 	best = moves;
		}
		print_solution(data->solution);
		ft_printf("Best moves = %d\n", best);
	}
}
