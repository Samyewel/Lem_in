/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:29:43 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/21 16:50:40 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** print_data:
** - Prints all data that has been stored.
*/

void	print_data(t_data *data, t_rooms *rooms, t_links *links)
{
	t_rooms	*ptr;

	ptr = rooms;
	ft_printf("\nAnt count: %d\n\n", data->ant_count);
	while (ptr)
	{
		ft_printf("Name: %s\n", ptr->name);
		ft_printf("x: %d\n", ptr->coord_x);
		ft_printf("y: %d\n", ptr->coord_y);
		ft_printf("Start? %d\n", ptr->start);
		ft_printf("End? %d\n\n", ptr->end);
		ptr = ptr->next;
	}
	if (links->a == NULL)
		ft_printf(""); //surpressing errors
}
