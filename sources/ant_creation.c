/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:29:46 by egaliber          #+#    #+#             */
/*   Updated: 2023/02/09 17:04:04 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
//#include "includes/lem_in.h"

// int	calculate_path(t_paths **path, int last)
// {
// 	int		edge;
// 	int		res;

// 	res = 1;
// 	edge = path[last]->length + 1;
// 	while (last > 0)
// 	{
// 		last--;
// 		res += (edge - path[last]->length);
// 	}
// 	return (res);
// }

// void	test_round(t_paths **paths, int nb_paths, int last)
// {
// 	int		edge;

// 	paths[last]->usage_times = 1;
// 	edge = paths[last]->length + 1;
// 	while (last > 0 && nb_paths > 0)
// 	{
// 		last--;
// 		paths[last]->usage_times = edge - paths[last]->length;
// 		nb_paths--;
// 	}
// }

// void	calculate_path_usage_times(t_data *data)
// {
// 	t_paths	**paths;
// 	int		remain;
// 	int 	last;
// 	int		i;

// 	i = 0;
// 	paths = data->solution->path;
// 	last = data->solution->path_count - 1;
// 	if (data->solution->path_count > 1)
// 	{
// 		test_round(paths, data->solution->path_count, last);
// 		remain = data->ant_count - calculate_path(paths, last);
// 		i = 0;
// 		while (i < data->solution->path_count)
// 		{
// 			paths[i]->usage_times += remain / data->solution->path_count;
// 			i++;
// 		}
// 		remain = remain % data->solution->path_count;
// 		i = 0;
// 		while (remain--)
// 		{
// 			paths[i]->usage_times++;
// 			i++;
// 		}
// 	}
// 	else
// 		data->solution->path[0]->usage_times = data->ant_count;
// }

void	init_ants(t_ants *new)
{
	new->ant_number = 0;
	new->next = NULL;
	new->room = NULL;
	new->room_location = NULL;
	new->has_moved = false;
	new->has_finished = false;
	new->index = 0;
	new->index_end = 0;
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
		clean_lem_in(heads, "Memory allocation failure in make_ants.");
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
