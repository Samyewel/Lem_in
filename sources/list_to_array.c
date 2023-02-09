/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:44:02 by sam               #+#    #+#             */
/*   Updated: 2023/02/09 16:03:13 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** room_list_to_array:
** - Converts the linked-list containing rooms into an array for easier data
**   access.
*/

void	room_list_to_array(t_heads *heads)
{
	t_rooms	**array;
	t_rooms	*temp_room;
	int		i;

	array = NULL;
	temp_room = heads->room_list;
	i = -1;
	array = (t_rooms **)malloc(sizeof(t_rooms *) * MAX_SIZE);
	if (!array)
		clean_lem_in(heads, "Memory allocation failure in path_list_to_array");
	ft_memset(array, 0, MAX_SIZE);
	while (temp_room)
	{
		array[++i] = temp_room;
		temp_room = temp_room->next;
	}
	heads->room = array;
}

/*
** path_list_to_array:
** - Converts the linked-list containing paths into an array for easier data
**   access.
*/

void	path_list_to_array(t_heads *heads)
{
	t_paths	**array;
	t_paths	*temp_path;
	int		i;

	array = NULL;
	temp_path = heads->path_list;
	i = -1;
	array = (t_paths **)malloc(sizeof(t_rooms *) * MAX_SIZE);
	if (!array)
		clean_lem_in(heads, "Memory allocation failure in path_list_to_array");
	ft_memset(array, 0, MAX_SIZE);
	while (temp_path)
	{
		array[++i] = temp_path;
		temp_path = temp_path->next;
	}
	heads->path = array;
}
