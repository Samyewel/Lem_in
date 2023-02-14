/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:30:16 by sam               #+#    #+#             */
/*   Updated: 2023/02/13 16:07:33 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

/*
** clean_lem_in:
** - Upon finding an error, all necessary data is cleaned before exiting the
**   program.
*/

void	clean_lem_in(t_heads *heads, char *str)
{
	ft_dprintf(1, str);
	if (heads->path)
		clean_path_array(heads);
	exit(EXIT_FAILURE);
}
