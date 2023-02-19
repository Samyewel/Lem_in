/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution_selection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:05:45 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/19 18:07:27 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** create_duplicate_path:
** - Duplicates the path to be stored in the solution array.
*/

static t_paths	*create_duplicate_path(t_paths *path, t_paths *previous)
{
	t_paths	*new_path;

	new_path = NULL;
	new_path = (t_paths *)malloc(sizeof(t_paths));
	if (!new_path)
		return (NULL);
	new_path->nb = path->nb;
	new_path->length = path->length;
	new_path->usage = path->usage;
	new_path->temp = path->temp;
	new_path->room = path->room;
	new_path->next = NULL;
	if (previous == NULL)
		new_path->previous = NULL;
	else
		new_path->previous = previous;
	return (new_path);
}

/*
** duplicate_path:
** - Locates the place in the array where the duplicated path will go.
** - Gives a pointer to the previous path for movement in later functions.
*/

static void	duplicate_path(t_solutions *solution, t_paths *path)
{
	int			i;

	i = -1;
	while (++i < MAX_SIZE)
	{
		if (solution->path[i] == NULL)
		{
			if (i == 0)
				solution->path[i] = create_duplicate_path(path, NULL);
			else
				solution->path[i] = \
				create_duplicate_path(path, solution->path[i - 1]);
			if (!solution->path[i])
				clean_lem_in("Memory allocation failure in duplicate_path.");
			break ;
		}
	}
}

/*
** store_paths_in_solution:
** - Takes the path indexes stored in the solution struct, and uses get_path
**   to return the pointer so that it can be duplicated and stored within
**   the solution struct itself.
*/

static void	store_paths_in_solution(
	t_heads *heads,
	t_solutions *solution)
{
	t_paths	*temp_path;
	int		i;

	temp_path = NULL;
	i = -1;
	solution->path = (t_paths **)malloc(sizeof(t_paths *) * \
			MAX_SIZE);
	if (!solution->path)
		clean_lem_in("Memory allocation failure in store_paths_in_solution.");
	while (++i < MAX_SIZE)
	{
		if (solution->path_indexes[i] >= 0)
		{
			temp_path = get_path(heads, solution->path_indexes[i]);
			duplicate_path(solution, temp_path);
		}
		else
			break ;
	}
}

/*
** store_solution:
** - Finds the index that would be best to accomdate the amount of ants
**   given.
** - Stored the best solution in the data struct for easy access.
** - Duplicates all paths using their indexes, storing them in the best
**   solution.
*/

void	store_solution(t_data *data, t_heads *heads)
{
	int	i;

	i = -1;
	while (++i < 1)
	{
		store_paths_in_solution(heads, heads->solution[i]);
		if (data->ant_count == 1)
			heads->solution[0]->path[0]->usage = data->ant_count;
		else
		{
			calculate_usage(data, heads->solution[i]);
			print_solution(heads->solution[i]);
		}
	}
	data->solution = heads->solution[0];
}
