/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:05:45 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/09 19:47:16 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** calculate_best_solution:
** - Finds the solution that has the closest length to the amount of ants.
** - If the ant count is 1, we return 0, as that path index will be the
**   shortest in the array.
*/

static int	calculate_best_solution(t_heads *heads, t_data *data)
{
	int			closest_length;
	int			closest_index;
	int			diff;
	int			i;

	closest_length = INT_MAX;
	closest_index = 0;
	i = -1;
	if (data->ant_count == 1)
		return (closest_index);
	while (++i < data->path_count)
	{
		if (heads->solution[i]->total_length <= data->ant_count)
		{
			diff = data->ant_count - heads->solution[i]->total_length;
			if (diff < closest_length)
			{
				closest_length = diff;
				closest_index = heads->solution[i]->nb;
			}
		}
	}
	return (closest_index);
}

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

static void	duplicate_path(t_data *data, t_paths *path)
{
	int			i;

	i = -1;
	while (++i < MAX_SIZE)
	{
		if (data->solution->path[i] == NULL)
		{
			if (i == 0)
				data->solution->path[i] = create_duplicate_path(path, NULL);
			else
				data->solution->path[i] = \
				create_duplicate_path(path, data->solution->path[i - 1]);
			if (!data->solution->path[i])
				ft_printf_strerror("Memory \
				allocation failure in duplicate_path.");
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
	t_data *data)
{
	t_paths	*temp_path;
	int		i;

	temp_path = NULL;
	i = -1;
	if (data->solution->path == NULL)
		data->solution->path = (t_paths **)malloc(sizeof (t_paths *) * \
			MAX_SIZE);
	if (!data->solution->path)
		clean_lem_in(heads, "Memory allocation failure in \
			store_paths_in_solution.");
	while (++i < MAX_SIZE)
	{
		if (data->solution->path_indexes[i] >= 0)
		{
			temp_path = get_path(heads, data->solution->path_indexes[i]);
			duplicate_path(data, temp_path);
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
	int			solution_index;

	solution_index = calculate_best_solution(heads, data);
	if (solution_index < 0)
		ft_printf_strerror("No solution found.");
	data->solution = heads->solution[solution_index];
	store_paths_in_solution(heads, data);
	if (DEBUG == true && SOLUTIONS == true)
		ft_printf("\nBest solution:\n");
	print_solution(data->solution);
}
