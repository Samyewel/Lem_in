/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution_creation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:09:20 by sam               #+#    #+#             */
/*   Updated: 2023/01/28 15:02:08 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** initialise_solution:
** -
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
	new_solution->paths = NULL;
	new_solution->total_length = (0 + path->length);
	new_solution->next = NULL;
	//ft_printf("Returning solution\n");
	return (new_solution);
}
