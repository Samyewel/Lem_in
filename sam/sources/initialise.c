/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:45:20 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/16 16:11:54 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	initialise_data(t_data *data)
{
	data->ant_count = 0;
}

static void	initialise_rooms(t_rooms *rooms)
{
	rooms->name = NULL;
	rooms->coord_x = -1;
	rooms->coord_y = -1;
	rooms->start = 0;
	rooms->start_searching = false;
	rooms->end = 0;
	rooms->end_searching = false;
	rooms->next = NULL;
	rooms->previous = NULL;
}

static void	initialise_links(t_links *links)
{
	links->a = NULL;
	links->b = NULL;
	links->next = NULL;
	links->previous = NULL;
}

void	initialise_structs(t_data *data, t_rooms *rooms, t_links *links)
{
	initialise_data(data);
	initialise_rooms(rooms);
	initialise_links(links);
}
