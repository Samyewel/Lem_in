/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:00:10 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/20 16:36:11 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** store_link:
** - Creates an array containing pointers to each link that a room links
**   to.
*/

void	store_link(t_rooms **rooms, char *link_a, char *link_b)
{
	t_rooms	*temp_room;
	t_rooms	*temp_link;
	int		i;

	i = -1;
	temp_room = find_room_name(rooms, link_a);
	temp_link = find_room_name(rooms, link_b);
	if (!temp_room || !temp_link)
		clean_lem_in("Invalid link name.");
	if (temp_room->links == NULL)
	{
		temp_room->links = (t_rooms **)ft_memalloc(sizeof(t_rooms *) * \
			MAX_SIZE);
		if (!temp_room->links)
			clean_lem_in("Memory allocation failure in store_link.");
	}
	while (++i < MAX_SIZE && temp_room->links[i] != NULL)
	{
		if (ft_strcmp(temp_room->links[i]->name, temp_link->name) == 0)
			clean_lem_in("Duplicate links for room.");
	}
	temp_room->links[i] = temp_link;
}
