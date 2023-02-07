/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:30:16 by sam               #+#    #+#             */
/*   Updated: 2023/02/07 17:12:15 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clean_path_list(t_heads *heads)
{
	t_paths	*current_path;
	t_paths	*next_path;
	t_rooms	*temp_room;
	t_rooms	*temp_data;
	int		i;

	current_path = heads->paths;
	next_path = NULL;
	temp_room = NULL;
	temp_data = NULL;
	while (current_path != NULL)
	{
		next_path = current_path->next;
		i = -1;
		while (++i < MAX_SIZE)
		{
			ft_strdel(&temp_room->name);
			free(temp_room);
		}
		free(current_path);
		current_path = next_path;
	}
	heads->paths = NULL;
}

void	clean_lem_in(t_data *data, t_heads *heads, char *str)
{
	ft_dprintf(2, "\e[4;31m[ERROR]\e[0m \e[4;37m%s\n\e[0m", str);
	if (heads->paths)
		clean_path_list(heads);
	// if (heads->rooms)
	// 	clean_rooms(heads);
	if (data)
		ft_printf("");
	exit(EXIT_FAILURE);
}