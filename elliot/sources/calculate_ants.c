/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ants.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:33:47 by egaliber          #+#    #+#             */
/*   Updated: 2023/02/01 14:55:14 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	calculate_min_for_path(t_paths *paths)
{
	t_paths	*temp;
	int		big_edge;
	int		res;

	res = 1;
	temp = paths;
	while (temp->next)
		temp = temp->next;
	big_edge = temp->length + 1;
	while (temp->previous)
	{
		temp = temp->previous;
		res += (big_edge - temp->length);
	}
	return (res);
}

void	deploy_first_round(t_paths *option, int nb_paths)
{
	//t_paths	*paths;
	int		big_edge;

	paths = option;
	while (paths->next)
		paths = paths->next;
	paths->usage_times = 1;
	big_edge = paths->length + 1;
	while (paths && nb_paths > 0)
	{
		paths = paths->previous;
		paths->usage_times = big_edge - paths->length;
		nb_paths--;
		if (!paths->previous)
			break ;
	}
	paths = NULL;
}

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
		deploy_first_round(data->solution->paths, data->soultion->path_count);
		remain = data->ant_count - calculate_min_for_path(temp);
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
		data->solution->paths = data->ant_count;
}
*/