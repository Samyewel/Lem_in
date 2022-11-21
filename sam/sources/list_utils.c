/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:53:38 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/21 16:22:28 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** initialise_rooms:
** -
*/

t_rooms	*create_room(t_rooms *room)
{
	room = (t_rooms *)malloc(sizeof (t_rooms));
	if (!room)
	{
		ft_printf("Memory allocation failure in %s on line %d.", __func__, __LINE__);
		exit(EXIT_FAILURE);
	}
	room->name = NULL;
	room->coord_x = 0;
	room->coord_y = 0;
	room->start = 0;
	room->end = 0;
	room->ants = 0;
	room->next = NULL;
	return (room);
}

/*
** initialise_links:
** -
*/

void	initialise_links(t_links *links)
{
	links->a = NULL;
	links->b = NULL;
	links->next = NULL;
}
