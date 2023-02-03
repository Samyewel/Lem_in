/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:39:05 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/03 14:45:15 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_paths	*get_path(t_heads *heads, int path_nb)
{
	t_paths	*temp_path;

	temp_path = heads->paths;
	while (temp_path)
	{
		if (temp_path->nb == path_nb)
			return (temp_path);
		temp_path = temp_path->next;
	}
	return (NULL);
}
