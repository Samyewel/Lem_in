/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:30:16 by sam               #+#    #+#             */
/*   Updated: 2023/02/13 13:53:55 by sam              ###   ########.fr       */
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

	i = -1;
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

static void	clean_room_list(t_heads *heads)
{
	t_rooms	*temp_room;
	t_rooms	*temp_data;
	int		i;

	i = -1;
	temp_room = heads->room_list;
	while (temp_room)
	{
		temp_data = temp_room->next;
		if (temp_room->links)
		{
			i = -1;
			while (i < MAX_SIZE)
				free(temp_room->links);
		}
		ft_strdel(&temp_room->name);
		free(temp_room);
		temp_room = temp_data;
	}
	free(heads->room_list);
}

/*
** clean_lem_in:
** - Upon finding an error, all necessary data is cleaned before exiting the
**   program.
*/

void	clean_lem_in(t_heads *heads, char *str)
{
	ft_dprintf(1, str);
	if (heads->path_list)
		clean_path_list(heads);
	if (heads->path)
		clean_path_array(heads);
	if (heads->room_list)
		clean_room_list(heads);
	exit(EXIT_FAILURE);
}
