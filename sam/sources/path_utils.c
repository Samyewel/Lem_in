/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:39:05 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/19 15:35:58 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** get_path:
** - Returns a pointer to a path using its path_nb.
*/

t_paths	*get_path(t_heads *heads, int path_nb)
{
	if (path_nb >= MAX_SIZE || path_nb < 0 || \
			heads->path[path_nb] == NULL)
		clean_lem_in("Invalid path_nb in get_path.");
	return (heads->path[path_nb]);
}

/*
** shortest_path:
** - Finds the shortest path in the array.
** - Used for when there is only one ant for the map.
*/

t_paths	*shortest_path(t_data *data, t_heads *heads)
{
	t_paths	*shortest_path;
	int		shortest_length;
	int		i;

	shortest_length = INT_MAX;
	shortest_path = 0;
	i = -1;
	while (++i < data->path_count)
	{
		if (heads->path[i]->length < shortest_length)
		{
			shortest_length = heads->path[i]->length;
			shortest_path = heads->path[i];
		}
	}
	return (shortest_path);
}
