/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:00:15 by sam               #+#    #+#             */
/*   Updated: 2023/02/03 18:39:03 by swilliam         ###   ########.fr       */
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

static int	paths_intersect(
t_heads *heads,
char *node_name,
t_solutions *solution)
{
	t_paths	*temp_path;
	t_rooms	*temp_node;
	int		i;

	temp_node = NULL;
	i = -1;
	while (++i < MAX_SIZE)
	{
		if (solution->path_indexes[i] >= 0)
		{
			temp_path = get_path(heads, solution->path_indexes[i]);
			temp_node = temp_path->path;
			while (temp_node)
			{
				if (ft_strcmp(node_name, temp_node->name) == 0)
					return (1);
				temp_node = temp_node->next;
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
	t_paths	*temp_path;
	t_rooms	*temp_node;
	bool	add;

	temp_path = heads->paths;
	while (temp_path)
	{
		add = false;
		temp_node = temp_path->path;
		while (temp_node && nb != temp_path->nb)
		{
			if (temp_node->is_room)
			{
				add = (!paths_intersect(heads, temp_node->name, solution));
				if (add == false)
					break ;
			}
			temp_node = temp_node->next;
		}
		if (add == true)
			add_to_solution(solution, temp_path);
		temp_path = temp_path->next;
	}
}

/*
** backtrack_paths:
** - Opens each path individually, creating a solution struct containing the
**   path and all paths that do not intersect with it.
*/

void	backtrack_paths(t_data *data, t_heads *heads)
{
	t_paths		*temp_path;
	int			i;

	i = 0;
	heads->solutions = initialise_solutions(data);
	if (!heads->solutions)
		ft_printf_strerror("Memory allocation failure in backtrack_paths.");
	if (data->ant_count == 1)
	{
		temp_path = find_shortest_path(heads);
		heads->solutions[0] = create_solution(heads, temp_path, 0);
	}
	else
	{
		temp_path = heads->paths;
		while (temp_path)
		{
			heads->solutions[i] = create_solution(heads, temp_path, i);
			check_intersections(heads, heads->solutions[i], temp_path->nb);
			if (heads->solutions[i]->path_count > 1)
				sort_solution_array(heads, heads->solutions[i]->path_indexes);
			temp_path = temp_path->next;
			i++;
		}
	}
}
