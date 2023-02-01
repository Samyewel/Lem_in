/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:29:46 by egaliber          #+#    #+#             */
/*   Updated: 2023/02/01 14:14:11 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
//#include "includes/lem_in.h"

void	calculate_path_usage_times(t_data *data)
{
	int	paths_l;
	int total_l;
	//int remain;
	t_paths *temp;
	
	ft_printf("number of paths = %d\n", data->solution->path_count);
	temp = data->solution->paths;
	paths_l = 0;
	total_l = 0;

	ft_printf("temp lenght = %d\n", temp->length);
	ft_printf("temp lenght = %d\n", temp->next->length);
	while (temp)
	{
		paths_l += temp->length;
		temp = temp->next;
	}
	ft_printf("paths combined lenght is = %d\n", paths_l);
	ft_printf("total lenght is = %d\n", total_l);
	total_l = (data->ant_count / paths_l) * data->solution->paths->length;
	ft_printf("total lenght is = %d\n", total_l);
	ft_printf("lenght of paths->length = %d\n", data->solution->paths->length);
	temp = data->solution->paths;
	//remain = data->ant_count - paths_l;
	while (temp->usage_times == 0)
	{
		if (temp->next == NULL)
		{
			ft_printf("does it neter if#1\n");
			temp->usage_times = total_l;
			temp = data->solution->paths;
		}
		if (temp == data->solution->paths)
		{
			temp->usage_times = data->ant_count - total_l;
			temp = temp->next;
		}
	}
	ft_printf("usage times is now = %d\n", data->solution->paths->usage_times);
	ft_printf("usage times for next is now = %d\n", data->solution->paths->next->usage_times);
}
/*
void	calculate_path_usage_times2(t_data *data)
{
	t_paths	*temp;
	t_paths	*paths;
	int		remain;

	paths = data->solution->paths;
	while(paths)
	{
		paths = paths->next;
	}
	temp = paths;
	if (data->solution->path_count > 1)
	{
		
	}
	else
		data->solution->paths = data->ant_count;
}
*/
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
