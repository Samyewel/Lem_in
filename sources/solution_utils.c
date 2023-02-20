/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:07:57 by egaliber          #+#    #+#             */
/*   Updated: 2023/02/20 11:29:09 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	calculate_remain(t_paths **paths, int remain, int path_count)
{
	int	i;

	remain = remain % path_count;
	i = 0;
	while (remain--)
	{
		if (remain < 0)
			break ;
		paths[i]->usage++;
		i++;
	}
}

int	calculate_path(t_paths **path, int last)
{
	int	edge;
	int	res;

	res = 1;
	edge = path[last]->length + 1;
	while (last > 0)
	{
		last--;
		res += (edge - path[last]->length);
	}
	return (res);
}

void	test_round(t_paths **paths, int nb_paths, int last)
{
	int	edge;

	paths[last]->usage = 1;
	edge = paths[last]->length + 1;
	while (last > 0 && nb_paths > 0)
	{
		last--;
		paths[last]->usage = edge - paths[last]->length;
		nb_paths--;
	}
}

void	calculate_path_use(t_data *data, t_solutions *solution, int path_count)
{
	t_paths	**paths;
	int		remain;
	int		last;
	int		i;

	i = 0;
	paths = solution->path;
	last = path_count - 1;
	if (path_count > 1)
	{
		test_round(paths, path_count, last);
		remain = data->ant_count - calculate_path(paths, last);
		i = 0;
		while (i < path_count)
		{
			paths[i]->usage += remain / path_count;
			i++;
		}
		calculate_remain(paths, remain, path_count);
	}
	else
		solution->path[0]->usage = data->ant_count;
}
