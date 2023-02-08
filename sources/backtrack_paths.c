/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:00:15 by sam               #+#    #+#             */
/*   Updated: 2023/02/08 14:26:04 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** add_to_solution:
** -
*/

static void	add_to_solution(t_solutions *solution, t_paths *add_path)
{
	int	i;

	i = -1;
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
		ft_printf_strerror("Memory allocation failure in create_solution.");
	if (i > 0)
		heads->solutions[i - 1]->next = new_solution;
	return (new_solution);
}

/*
** paths_intersect:
** -
*/

static int	intersect(
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
** -
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
			intersect = false;
			while (++x < MAX_SIZE)
			{
				if (heads->path[i]->room[x] == NULL)
					break ;
				if (heads->path[i]->room[x]->is_room)
				{
					intersect = intersect(heads, heads->path[i]->room[x]->id, solution);
					if (intersect == true)
						break ;
				}
			}
			if (intersect == false)
				add_to_solution(solution, heads->path[i]);
		}
	}
}

/*
** backtrack_paths:
** - Opens each path individually, creating a solution struct containing the
**   path and all paths that do not intersect with it.
*/

void	backtrack_paths(t_data *data, t_heads *heads)
{
	int	i;

	i = -1;
	ft_printf("Backtracking paths...\n");
	heads->solutions = initialise_solutions(data);
	if (!heads->solutions)
		ft_printf_strerror("Memory allocation failure in backtrack_paths.");
	if (data->ant_count == 1)
		heads->solutions[0] = create_solution(heads, find_shortest_path(data, heads), 0);
	else
	{
		while (++i < MAX_SIZE)
		{
			if (heads->path[i] == NULL)
				break ;
			heads->solutions[i] = create_solution(heads, heads->path[i], i);
			check_intersections(heads, heads->solutions[i], heads->path[i]->nb);
			if (heads->solutions[i]->path_count > 1)
				sort_solution_array(heads, heads->solutions[i]->path_indexes);
			print_solution(heads->solutions[i]);
		}
	}
}
