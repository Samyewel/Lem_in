/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:00:15 by sam               #+#    #+#             */
/*   Updated: 2023/01/27 15:11:00 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** add_to_solution:
** -
*/

static void	add_to_solution(t_heads *heads, t_paths *path, t_paths *add_path)
{
	t_solutions	*temp_solutions;
	int			i;

	temp_solutions = heads->solutions;
	i = -1;
	while (temp_solutions)
	{
		if (temp_solutions->nb == path->nb)
		{
			while (++i < MAX_SIZE)
			{
				if (temp_solutions->paths[i] < 0)
				{
					temp_solutions->paths[i] = add_path->nb;
					temp_solutions->total_length += add_path->length;
					break ;
				}
			}
			return ;
		}
		temp_solutions = temp_solutions->next;
	}
}

/*
** create_solution:
** -
*/

static void	create_solution(
t_heads *heads,
t_paths *path
)
{
	t_solutions	*temp_solution;
	t_solutions	*new_solution;

	temp_solution = heads->solutions;
	new_solution = initialise_solution(path);
	if (!new_solution)
		ft_printf_strerror("Memory allocation failure in create_solution.");
	if (heads->solutions == NULL)
		heads->solutions = new_solution;
	else
	{
		while (temp_solution->next != NULL)
			temp_solution = temp_solution->next;
		temp_solution->next = new_solution;
		temp_solution = temp_solution->next;
	}
}

/*
** paths_intersect:
** -
*/

static int	paths_intersect(char *node_name, t_paths *path2)
{
	t_rooms	*temp_node;

	temp_node = path2->path;
	while (temp_node)
	{
		if (temp_node->is_room && ft_strcmp(node_name, temp_node->name) == 0)
			return (1);
		temp_node = temp_node->next;
	}
	return (0);
}

/*
** check_intersections:
** -
*/

static void	check_intersections(t_heads *heads, t_paths *path)
{
	t_paths	*temp_path;
	t_rooms	*temp_node;
	bool	add;

	temp_path = heads->paths;
	temp_node = NULL;
	while (temp_path)
	{
		if (temp_path->nb != path->nb)
		{
			add = true;
			temp_node = path->path;
			while (temp_node)
			{
				add = (!paths_intersect(temp_node->name, temp_path));
				if (add == false)
					break ;
				temp_node = temp_node->next;
			}
			if (add == true)
				add_to_solution(heads, path, temp_path);
		}
		temp_path = temp_path->next;
	}
}

/*
** backtrack_paths:
** -
*/

void	backtrack_paths(t_heads *heads)
{
	t_paths	*temp_path;

	temp_path = heads->paths;
	while (temp_path)
	{
		create_solution(heads, temp_path);
		check_intersections(heads, temp_path);
		temp_path = temp_path->next;
	}
	print_solutions(heads);
}
