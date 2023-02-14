/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage_calculation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:17:07 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/14 12:44:29 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** reset_usage:
** - Resets the usage of each path in the solution's array to 0 in preparation
**   for another distribution attempt.
** - Initialises the turns array to store how many turns each path will need.
*/

static void	reset_usage(
	t_heads *heads,
	t_solutions *solution,
	int **turns,
	int path_count)
{
	int	i;

	i = -1;
	*turns = (int *)malloc(sizeof(int) * path_count);
	if (!(*turns))
		clean_lem_in(heads, "Memory allocation failure in reset_usage.");
	while (++i < solution->path_count)
		solution->path[i]->usage = 0;
}

/*
** longest move:
** - Finds the highest amount of turns the current solution will take.
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
** - Distributes the path usage among the amount of necessary paths.
** - Calculates the amount of turns the current path will take with it's
**   usage and length, storing it in an array.
** - The amount of turns this solution's path usages will take is equal
**   to the longest path turns in the array.
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
	reset_usage(heads, solution, &turns, path_count);
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
** swap_usages:
** - There are two cases where usages need to be swapped:
**   - If the current usages take too many turns, we reverse the results
**     given by swapping the path usage back to it's previous results.
**   - If we are satisfied with the turns the current usage distribution,
**     we set the current usage to the previous results so that they can
**     be reverted later in case the next test takes too many turns.
*/

static void	swap_usages(t_solutions *solution, int reverse)
{
	int	i;

	i = -1;
	if (reverse == 0)
	{
		solution->paths_used--;
		while (++i < solution->paths_used)
			solution->path[i]->usage = solution->path[i]->previous_usage;
	}
	else
	{
		while (++i < solution->paths_used)
			solution->path[i]->previous_usage = solution->path[i]->usage;
	}
}

/*
** calculate_usage:
** - If there are more than one ant or path, we distribute the usages amongst
**   the necessary paths, stopping before the next path would cause there
**   to be too many turns used.
** - If the path count of the solution is one, then the while loop will not be
**   met and all ants will be given to the first path.
*/

void	calculate_usage(t_data *data, t_heads *heads, t_solutions *solution)
{
	int	i;
	int	current;
	int	previous;

	i = -1;
	previous = distribute(data, heads, solution, solution->paths_used);
	swap_usages(solution, 1);
	solution->turns = previous;
	while (++i < solution->path_count)
	{
		if (solution->paths_used == solution->path_count)
			break ;
		solution->paths_used++;
		current = distribute(data, heads, solution, solution->paths_used);
		if (previous <= current)
		{
			swap_usages(solution,0);
			break ;
		}
		previous = current;
		solution->turns = previous;
		swap_usages(solution, 1);
	}
}
