/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution_usage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:17:07 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/21 15:24:42 by swilliam         ###   ########.fr       */
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
	t_solutions *solution,
	int **turns,
	int path_count)
{
	int	i;

	i = -1;
	*turns = (int *)malloc(sizeof(int) * path_count);
	if (!turns)
		clean_lem_in("Memory allocation failure in reset_usage.");
	while (++i < solution->path_count)
		solution->path[i]->usage = 0;
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
	t_solutions *solution,
	int path_count)
{
	int	i;
	int	*turns;
	int	ants_left;

	ants_left = data->ant_count;
	turns = NULL;
	reset_usage(solution, &turns, path_count);
	i = -1;
	if (path_count > 0)
	{
		calculate_path_use(data, solution, path_count);
		while (++i < path_count)
			turns[i] = solution->path[i]->length + solution->path[i]->usage;
	}
	return (longest_move(turns, path_count));
}

/*
** swap_usages:
** - Swaps the usage between the temporary and current usage counts
**   for when we are calculating which usage results in the shortest
**   amoun of turns.
*/

static void	swap_usages(t_solutions *solution, int reverse)
{
	int	i;

	i = -1;
	if (reverse == 0)
	{
		solution->paths_used--;
		while (++i < solution->paths_used)
			solution->path[i]->usage = solution->path[i]->temp_usage;
	}
	else
	{
		while (++i < solution->paths_used)
			solution->path[i]->temp_usage = solution->path[i]->usage;
	}
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

void	calculate_usage(t_data *data, t_solutions *solution)
{
	int	i;
	int	current;
	int	previous;

	i = -1;
	previous = distribute(data, solution, solution->paths_used);
	swap_usages(solution, 1);
	solution->turns = previous;
	while (++i < solution->path_count)
	{
		if (solution->paths_used == solution->path_count)
			break ;
		solution->paths_used++;
		current = distribute(data, solution, solution->paths_used);
		if (previous <= current)
		{
			swap_usages(solution, 0);
			break ;
		}
		previous = current;
		solution->turns = previous;
		swap_usages(solution, 1);
	}
}
