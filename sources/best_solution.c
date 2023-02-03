/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:05:45 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/02 17:29:53 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	calculate_best_solution(t_heads *heads, t_data *data)
{
	t_solutions	*temp_solution;
	int			closest_length;
	int			closest_index;
	int			diff;

	temp_solution = heads->solutions;
	closest_length = INT_MAX;
	closest_index = -1;
	while (temp_solution)
	{
		if (temp_solution->total_length <= data->ant_count)
		{
			diff = data->ant_count - temp_solution->total_length;
			if (diff < closest_length)
			{
				closest_length = diff;
				closest_index = temp_solution->nb;
			}
		}
		temp_solution = temp_solution->next;
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
	new_path->path = path->path;
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

static void	store_paths_in_solution(t_heads *heads, t_data *data)
{
	t_paths	*temp_path;
	int		i;

	temp_path = heads->paths;
	i = -1;
	while (++i < MAX_SIZE)
	{
		if (data->solution->path_indexes[i] >= 0)
		{
			//ft_printf("Storing path %d\n", data->solution->path_indexes[i]);
			temp_path = heads->paths;
			while (temp_path)
			{
				if (temp_path->nb == data->solution->path_indexes[i])
					duplicate_path(data, temp_path);
				temp_path = temp_path->next;
			}
			//ft_printf("Stored successfully\n");
		}
		else
			break ;
	}
}

void	store_solution(t_heads *heads, t_data *data)
{
	t_solutions	*temp_solution;
	int			solution_index;

	ft_printf("Storing solution\n");
	solution_index = calculate_best_solution(heads, data);
	if (solution_index < 0)
		ft_printf_strerror("No solution found.");
	temp_solution = heads->solutions;
	if (!temp_solution)
		ft_printf_strerror("No solution stored.");
	while (temp_solution)
	{
		if (temp_solution->nb == solution_index)
		{
			data->solution = temp_solution;
			store_paths_in_solution(heads, data);
			break ;
		}
		temp_solution = temp_solution->next;
	}
}
