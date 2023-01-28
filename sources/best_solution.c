/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:05:45 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/28 13:39:45 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	calculate_best_solution(t_heads *heads, t_data *data)
{
	t_solutions	*temp_solution;
	int			closest_length;
	int			closest_index;
	int			diff;

	temp_solution = heads->solutions;
	closest_length = INT_MAX;
	closest_index = -1;
	while (temp_solution)
	{
		if (temp_solution->total_length <= data->ant_count)
		{
			diff = data->ant_count - temp_solution->total_length;
			if (diff < closest_length)
			{
				closest_length = diff;
				closest_index = temp_solution->nb;
			}
		}
		temp_solution = temp_solution->next;
	}
	return (closest_index);
}
