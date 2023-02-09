/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:17:07 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/09 20:51:16 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** sort_solution:
** - Sorts the solution path index array in ascending length order.
*/

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

static void	reset_usage(t_solutions *solution)
{
	int	i;

	i = -1;
	while (++i < solution->path_count)
	{
		if (solution->path[i]->usage != 0)
			solution->path[i]->usage = 0;
	}
}

static int	longest_move(int *turns, int path_count)
{
	int	most_turns;
	int	i;

	most_turns = 0;
	i = -1;
	while (++i < path_count)
	{
		if (most_turns < turns[i])
			most_turns = turns[i];
	}
	return (most_turns);
}

static int	distribute_usage(
	t_data *data,
	t_heads *heads,
	t_solutions *solution,
	int path_count)
{
	int	i;
	int	*turns;
	int	ants_left;

	turns = (int *)malloc(sizeof(int) * path_count);
	if (!turns)
		clean_lem_in(heads, "Memory allocation failure in distribute_usage");
	ants_left = data->ant_count;
	reset_usage(solution);
	while (ants_left > 0)
	{
		i = -1;
		while (++i < path_count)
			turns[i] = solution->path[i]->length + solution->path[i]->usage;
		i = -1;
		while (++i < path_count && ants_left > 0)
		{
			if (solution->path[i]->usage < turns[i])
			{
				solution->path[i]->usage++;
				ants_left--;
			}
		}
	}
	return (longest_move(turns, path_count));
}

void	calculate_usage(t_data *data, t_heads *heads, t_solutions *solution)
{
	int	i;

	i = -1;
	ft_printf("\nCalculating usage with %d ants.\n", data->ant_count);
	if (data->ant_count == 1 || solution->path_count == 1)
	{
		solution->path[0]->usage = data->ant_count;
		return ;
	}
	while (++i < solution->path_count)
	{
		++solution->paths_used;
		if (solution->path[i + 1] != NULL && \
		distribute_usage(data, heads, solution, solution->paths_used + 1) > \
		distribute_usage(data, heads, solution, solution->paths_used))
			break ;
	}
	i = -1;
	while (++i < data->solution->path_count)
		ft_printf("Path %d used %d times.\n", \
		data->solution->path[i]->nb, data->solution->path[i]->usage);
}
