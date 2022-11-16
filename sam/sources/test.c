/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:29:43 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/16 16:43:13 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** print_data:
** - Prints all data that has been stored.
*/

void	print_data(t_data *data, t_rooms *rooms, t_links *links)
{
	ft_printf("data->ant_count == %d\n\n", data->ant_count);
	while (rooms)
	{
		ft_printf("Name: %s\n", rooms->name);
		ft_printf("x: %d\n", rooms->coord_x);
		ft_printf("y:%d\n", rooms->coord_y);
		ft_printf("Start? %d\n", rooms->start);
		ft_printf("End? %d\n\n", rooms->end);
		rooms = rooms->next;
	}
	if (links->a == NULL)
		ft_printf(""); //surpressing errors
}
