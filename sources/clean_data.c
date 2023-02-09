/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:30:16 by sam               #+#    #+#             */
/*   Updated: 2023/02/09 12:49:07 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** clean_path_list:
** - Frees all data within the path_list, different from the array that is
**   created by duplicating the list.
*/

void	clean_path_list(t_heads *heads)
{
	t_paths	*current_path;
	t_paths	*next_path;
	t_rooms	*temp_room;
	int		i;

	current_path = heads->path_list;
	next_path = NULL;
	temp_room = NULL;
	while (current_path)
	{
		next_path = current_path->next;
		i = -1;
		while (++i < MAX_SIZE)
		{
			if (temp_room->name)
				ft_strdel(&temp_room->name);
			free(temp_room);
		}
		free(current_path);
		current_path = next_path;
	}
	heads->path_list = NULL;
}

void	clean_path_array(t_heads *heads)
{
	int	i;
	int	x;

	i = -1
	while (++i < MAX_SIZE)
	{
		if (heads->path[i] == NULL)
			break ;
		else
		{
			x = -1;
			while (x < MAX_SIZE)
			{
				if (heads->path[i]->room[x] == NULL)
					break ;
				else
				{
					ft_strdel(&heads->path[i]->room[x]->name);
					free(heads->path[i]->room[x]);
				}
			}
			free(heads->path[i]);
		}
	}
	free(heads->path);
}

/*
** clean_lem_in:
** - Upon finding an error, all necessary data is cleaned before exiting the
**   program.
*/

void	clean_lem_in(t_data *data, t_heads *heads, char *str)
{
	ft_dprintf(2, "\e[4;31m[ERROR]\e[0m \e[4;37m%s\n\e[0m", str);
	if (heads->path_list)
		clean_path_list(heads);
	// if (heads->rooms)
	// 	clean_rooms(heads);
	if (data)
		ft_printf("");
	exit(EXIT_FAILURE);
}
