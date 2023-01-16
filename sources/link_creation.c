/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:00:10 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/16 21:45:07 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** create_link:
** - Creates a fresh link to be added to a list.
** - Takes the name of a linked room and modifies the link's name.
*/

static t_links	*create_link(char *link_name)
{
	t_links	*link;

	link = (t_links *)malloc(sizeof(t_rooms));
	if (!link)
		ft_printf_strerror("Memory allocation failure in create_link.");
	link->name = ft_strdup(link_name);
	if (!link->name)
		ft_printf_strerror("Memory allocation failure in create_link.");
	link->next = NULL;
	return (link);
}

/*
** add_link:
** - Creates a linked list containing each neigbouring room that a room
**   links to.
*/

t_links	*store_link(t_rooms **rooms, char *link_a, char *link_b)
{
	t_links	*link;
	t_rooms	*temp_room;
	t_links	*temp_link;

	link = NULL;
	link = create_link(link_b);
	temp_link = NULL;
	temp_room = find_room(rooms, link_a);
	if (temp_room->links == NULL)
		temp_room->links = link;
	else
	{
		temp_link = temp_room->links;
		while (temp_link->next != NULL)
			temp_link = temp_link->next;
		temp_link->next = link;
	}
	return (link);
}
