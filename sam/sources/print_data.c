/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:29:43 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/23 16:03:03 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Remove before submission
** print_data:
** - Prints all data that has been stored.
*/

void	print_data(t_data *data, t_rooms *rooms)
{
	t_rooms	*ptr;
	t_links	*link;
	t_rooms	*start;
	t_rooms	*end;

	start = find_start_room(&rooms);
	end = find_end_room(&rooms);
	ft_printf("Starting room: %s\n", start->name);
	ft_printf("Ending room: %s\n", end->name);

	ptr = rooms;
	ft_printf("\nAnt count: %d\n\n", data->ant_count);
	while (ptr)
	{
		ft_printf("Name: %s\n", ptr->name);
		ft_printf("x: %d\n", ptr->coord_x);
		ft_printf("y: %d\n", ptr->coord_y);
		ft_printf("Start? %d\n", ptr->start);
		ft_printf("End? %d\n", ptr->end);
		link = ptr->links;
		while (link)
		{
			ft_printf("Links to: %s\n", link->name);
			link = link->next;
		}
		ft_printf("\n");
		ptr = ptr->next;
	}
}
