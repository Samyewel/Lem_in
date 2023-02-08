/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:05:45 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/08 12:24:18 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
		if (heads->solutions[i]->total_length <= data->ant_count)
		{
			diff = data->ant_count - heads->solutions[i]->total_length;
			if (diff < closest_length)
			{
				closest_length = diff;
				closest_index = heads->solutions[i]->nb;
			}
		}
	}
	return (closest_index);
}

static t_paths	*create_duplicate_path(t_paths *path, t_paths *previous)
{
	t_paths	*new_path;

	new_path = NULL;
	new_path = (t_paths *)malloc(sizeof(t_paths));
	if (!new_path)
		return (NULL);
	new_path->nb = path->nb;
	new_path->length = path->length;
	new_path->usage_times = path->usage_times;
	new_path->temp = path->temp;
	new_path->room = path->room;
	new_path->next = NULL;
	if (previous == NULL)
		new_path->previous = NULL;
	else
		new_path->previous = previous;
	return (new_path);
}

static void	duplicate_path(t_data *data, t_paths *path)
{
	t_paths		*temp_path;
	t_paths		*temp_solution_path;

	if (data->solution->temp_previous == NULL)
		temp_path = create_duplicate_path(path, NULL);
	else
		temp_path = create_duplicate_path(path, data->solution->temp_previous);
	temp_solution_path = data->solution->paths;
	if (!temp_path)
		ft_printf_strerror("Memory allocation failure in duplicate_path.");
	if (data->solution->paths == NULL)
		data->solution->paths = temp_path;
	else
	{
		while (temp_solution_path->next != NULL)
			temp_solution_path = temp_solution_path->next;
		temp_solution_path->next = temp_path;
	}
	data->solution->temp_previous = temp_path;
}

/*
** store_paths_in_solution:
** -
*/

static void	store_paths_in_solution(
	t_heads *heads,
	t_data *data)
{
	t_paths	*temp_path;
	int		i;

	temp_path = NULL;
	i = -1;
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

void	store_solution(t_data *data, t_heads *heads)
{
	int			solution_index;

	ft_printf("Calculating solution...\n");
	solution_index = calculate_best_solution(heads, data);
	if (solution_index < 0)
		ft_printf_strerror("No solution found.");
	data->solution = heads->solutions[solution_index];
	store_paths_in_solution(heads, data);
}
