/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:00:15 by sam               #+#    #+#             */
/*   Updated: 2023/02/09 20:02:03 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** add_to_solution:
** - Adds the path number to the array stored within the solution struct.
** - Adds the path length onto the total length of the solution.
** - Increases the count to indicate how many paths are stored within the
**   solution.
*/

static void	add_to_solution(bool b, t_solutions *solution, t_paths *add_path)
{
	int	i;

	i = -1;
	if (b == true)
		return ;
	while (++i < MAX_SIZE)
	{
		if (solution->path_indexes[i] < 0)
		{
			solution->path_indexes[i] = add_path->nb;
			solution->total_length += add_path->length;
			solution->path_count++;
			break ;
		}
	}
	return ;
}

/*
** create_solution:
** -
*/

static t_solutions	*create_solution(
t_heads *heads,
t_paths *path,
int i
)
{
	t_solutions	*new_solution;

	new_solution = initialise_solution(path);
	if (!new_solution)
		clean_lem_in(heads, "Memory allocation failure in create_solution.");
	if (i > 0)
		heads->solution[i - 1]->next = new_solution;
	return (new_solution);
}

/*
** intersect:
** - Takes the id of a room from a path, and loops through all paths within
**   the given solution to ensure it does not intersect with any of them.
*/

static int	intersects(
t_heads *heads,
int node_id,
t_solutions *solution)
{
	t_paths	*temp_path;
	int		i;
	int		x;

	i = -1;
	while (++i < MAX_SIZE)
	{
		if (solution->path_indexes[i] >= 0)
		{
			temp_path = get_path(heads, solution->path_indexes[i]);
			x = -1;
			while (++x < MAX_SIZE)
			{
				if (temp_path->room[x] == NULL)
					break ;
				if (temp_path->room[x]->is_room \
				&& temp_path->room[x]->id == node_id)
					return (1);
			}
		}
		else
			break ;
	}
	return (0);
}

/*
** check_intersections:
** - Loops through all paths stored from backtrack_rooms to find all paths
**   that do not intersect with any paths in the current solution.
** - Calls add_to_solution if a path does not intersect, storing it in the
**   array of path indexes inside the solution.
*/

static void	check_intersections(t_heads *heads, t_solutions *solution, int nb)
{
	int		i;
	int		x;
	bool	b;

	i = -1;
	while (++i < MAX_SIZE)
	{
		if (heads->path[i] == NULL)
			break ;
		if (heads->path[i]->nb != nb)
		{
			x = -1;
			b = false;
			while (++x < MAX_SIZE)
			{
				if (heads->path[i]->room[x] == NULL)
					break ;
				if (heads->path[i]->room[x]->is_room)
				{
					b = intersects(heads, heads->path[i]->room[x]->id, solution);
					if (b == true)
						break ;
				}
			}
			add_to_solution(b, solution, heads->path[i]);
		}
	}
}

/*
** backtrack_paths:
** - Opens each path individually, creating a solution struct containing the
**   path index and all those that do not intersect with it or others within
**   that solution.
** - Calls sort_solution_array to sort the array of path indexes in ascending
**   length order.
*/

void	backtrack_paths(t_data *data, t_heads *heads)
{
	int	i;

	i = -1;
	heads->solution = initialise_solutions(data);
	if (!heads->solution)
		clean_lem_in(heads, "Memory allocation failure in backtrack_paths.");
	if (data->ant_count == 1)
		heads->solution[0] = \
		create_solution(heads, shortest_path(data, heads), 0);
	else
	{
		while (++i < MAX_SIZE)
		{
			if (heads->path[i] == NULL)
				break ;
			heads->solution[i] = create_solution(heads, heads->path[i], i);
			check_intersections(heads, heads->solution[i], heads->path[i]->nb);
			if (heads->solution[i]->path_count > 1)
				sort_solution(heads, heads->solution[i]->path_indexes);
		}
	}
}
