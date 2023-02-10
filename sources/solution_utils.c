/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:17:07 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/10 12:46:15 by sam              ###   ########.fr       */
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

/*
** reset_usage:
** - Resets the usage of each path in the solution's array to 0 in preparation
**   for another distribution attempt.
** - Initialises the turns array to store how many turns each path will need.
*/

static int	*reset_usage(
	t_heads *heads,
	t_solutions *solution,
	int path_count)
{
	int	i;
	int	*new_turns;

	new_turns = NULL;
	i = -1;
	while (++i < solution->path_count)
	{
		if (solution->path[i]->usage != 0)
			solution->path[i]->usage = 0;
	}
	new_turns = (int *)malloc(sizeof(int) * path_count);
	if (!new_turns)
		clean_lem_in(heads, "Memory allocation failure in reset_usage.");
	return (new_turns);
}

/*
** longest move:
** - Finds which path contains the longest amount of moves.
*/

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
	free(turns);
	return (most_turns);
}

/*
** distribute:
** - Distributes the path usage among the amount of necessary paths
*/

static int	distribute(
	t_data *data,
	t_heads *heads,
	t_solutions *solution,
	int path_count)
{
	int	i;
	int	*turns;
	int	ants_left;

	ants_left = data->ant_count;
	turns = NULL;
	turns = reset_usage(heads, solution, path_count);
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

/*
** calculate_usage:
** - When there is either one ant or one path, the fastest method is to
**   send all ants through the shortest path, which will always be the first
**   path in the array.
** - If there are more than one ant or path, we distribute the usages amongst
**   the necessary paths, stopping before the next path would cause there
**   to be too many turns used.
*/

void	calculate_usage(t_data *data, t_heads *heads, t_solutions *solution)
{
	int	i;
	int	current;
	int	previous;

	i = -1;
	if (data->ant_count == 1 || solution->path_count == 1)
	{
		data->solution->paths_used = 1;
		solution->path[0]->usage = data->ant_count;
		return ;
	}
	if (solution->paths_used > 1)
		previous = distribute(data, heads, solution, solution->paths_used);
	while (++i < solution->path_count)
	{
		++solution->paths_used;
		current = distribute(data, heads, solution, solution->paths_used);
		if (i > 0 && solution->path[i - 1] && previous <= current)
			break ;
		previous = current;
	}
}
