/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution_creation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:09:20 by sam               #+#    #+#             */
/*   Updated: 2023/01/27 15:11:14 by sam              ###   ########.fr       */
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
	new_solution->paths = (int *)malloc(sizeof(int) * MAX_SIZE);
	if (!new_solution->paths)
		return (NULL);
	ft_memset(new_solution->paths, -1, MAX_SIZE);
	new_solution->paths[0] = path->nb;
	new_solution->nb = path->nb;
	new_solution->total_length = (0 + path->length);
	new_solution->next = NULL;
	return (new_solution);
}
