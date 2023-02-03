/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:29:46 by egaliber          #+#    #+#             */
/*   Updated: 2023/02/03 13:02:27 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
//#include "includes/lem_in.h"

int	calculate_path(t_paths *paths)
{
	t_paths	*temp;
	int		edge;
	int		res;

	res = 1;
	temp = paths;
	while (temp->next)
		temp = temp->next;
	edge = temp->length + 1;
	while (temp->previous)
	{
		temp = temp->previous;
		res += (edge - temp->length);
	}
	return (res);
}

void	test_round(t_paths *head, int nb_paths)
{
	t_paths	*paths;
	int		edge;

	paths = head;
	while (paths->next)
		paths = paths->next;
	paths->usage_times = 1;
	edge = paths->length + 1;
	while (paths && nb_paths > 0)
	{
		paths = paths->previous;
		paths->usage_times = edge - paths->length;
		nb_paths--;
		if (!paths->previous)
			break ;
	}
	paths = NULL;
}

void	calculate_path_usage_times(t_data *data)
{
	t_paths	*temp;
	t_paths	*paths;
	int		remain;

	paths = data->solution->paths;
	while (paths)
	{
		paths = paths->next;
	}
	temp = paths;
	if (data->solution->path_count > 1)
	{
		test_round(data->solution->paths, data->solution->path_count);
		remain = data->ant_count - calculate_path(data->solution->paths);
		temp = data->solution->paths;
		while (temp)
		{
			temp->usage_times += remain / data->solution->path_count;
			temp = temp->next;
		}
		remain = remain % data->solution->path_count;
		temp = data->solution->paths;
		while (remain--)
		{
			temp->usage_times++;
			temp = temp->next;
		}
	}
	else
		data->solution->paths->usage_times = data->ant_count;
}

void	init_ants(t_ants *new)
{
	new->ant_number = 0;
	new->next = NULL;
	new->room = NULL;
	new->room_location = NULL;
	new->has_moved = false;
	new->has_finished = false;
}

t_ants	*make_new_ant(t_data *data, t_ants *new)
{
	new = (t_ants *)malloc(sizeof(t_ants));
	if (!new)
		return (NULL);
	init_ants(new);
	data->ant_num++;
	new->ant_number = data->ant_num;
	return (new);
}

t_ants	*make_ants(t_data *data, t_ants *ants, t_heads *heads)
{
	t_ants	*new_ant;

	new_ant = NULL;
	new_ant = make_new_ant(data, new_ant);
	if (!new_ant)
		ft_printf_strerror("Memory allocation failure in make_ants.");
	if (heads->ants == NULL)
	{
		ants = new_ant;
		heads->ants = new_ant;
	}
	else
	{
		ants->next = new_ant;
		ants = ants->next;
	}
	return (ants);
}
