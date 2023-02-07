/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:44:02 by sam               #+#    #+#             */
/*   Updated: 2023/02/06 14:35:42 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms	**room_list_to_array(t_heads *heads)
{
	t_rooms	**array;
	t_rooms	*temp_room;
	int		i;

	array = NULL;
	temp_room = heads->rooms;
	i = -1;
	array = (t_rooms **)malloc(sizeof(t_rooms *) * MAX_SIZE);
	if (!array)
		return (NULL);
	ft_memset(array, 0, MAX_SIZE);
	while (temp_room)
	{
		array[++i] = temp_room;
		temp_room = temp_room->next;
	}
	return (array);
}

t_paths	**path_list_to_array(t_heads *heads)
{
	t_paths	**array;
	t_paths	*temp_path;
	int		i;

	array = NULL;
	temp_path = heads->paths;
	i = -1;
	array = (t_paths **)malloc(sizeof(t_rooms *) * MAX_SIZE);
	if (!array)
		return (NULL);
	ft_memset(array, 0, MAX_SIZE);
	while (temp_path)
	{
		array[++i] = temp_path;
		temp_path = temp_path->next;
	}
	return (array);
}
