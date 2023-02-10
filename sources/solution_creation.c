/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution_creation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:09:20 by sam               #+#    #+#             */
/*   Updated: 2023/02/10 10:26:00 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** initialise_solution:
** - Initialises a fresh solution with necessary data for calculating the best
**   solution.
*/

t_solutions	*initialise_solution(t_paths *path)
{
	t_solutions	*new_solution;

	new_solution = NULL;
	new_solution = (t_solutions *)malloc(sizeof(t_solutions));
	if (!new_solution)
		return (NULL);
	new_solution->path_indexes = (int *)malloc(sizeof(int) * MAX_SIZE);
	if (!new_solution->path_indexes)
		return (NULL);
	ft_memset(new_solution->path_indexes, -1, MAX_SIZE);
	new_solution->path_indexes[0] = path->nb;
	new_solution->nb = path->nb;
	new_solution->path_count = 1;
	new_solution->paths_used = 0;
	new_solution->path = NULL;
	new_solution->total_length = (0 + path->length);
	new_solution->next = NULL;
	new_solution->temp_previous = NULL;
	return (new_solution);
}

/*
** initialise_solutions:
** - Initialises the array solutions head.
*/

t_solutions	**initialise_solutions(t_data *data)
{
	t_solutions	**solutions_index;

	solutions_index = NULL;
	if (data->ant_count == 1)
		solutions_index = (t_solutions **)malloc(sizeof(t_solutions *) * 1);
	else
		solutions_index = \
			(t_solutions **)malloc(sizeof(t_solutions *) * data->path_count);
	if (!solutions_index)
		return (NULL);
	return (solutions_index);
}
