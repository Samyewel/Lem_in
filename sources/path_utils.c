/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:39:05 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/06 14:56:20 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_paths	*get_path(t_heads *heads, int path_nb)
{
	if (path_nb >= MAX_SIZE || path_nb < 0 || \
			heads->path_array[path_nb] == NULL)
		ft_printf_strerror("Invalid path_nb in get_path.");
	return (heads->path_array[path_nb]);
}
