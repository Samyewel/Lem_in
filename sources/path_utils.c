/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:39:05 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/09 16:05:09 by egaliber         ###   ########.fr       */
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
		clean_lem_in(heads, "Invalid path_nb in get_path.");
	return (heads->path[path_nb]);
}
