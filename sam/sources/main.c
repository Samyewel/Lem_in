/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:16:16 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/22 14:49:38 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** lem-in:
** -
*/

int	main(void)
{
	t_data	*data;
	t_rooms	*rooms;
	t_links	*links;

	data = NULL;
	rooms = NULL;
	links = NULL;
	data = initialise_data(data);
	if (!data)
		ft_printf_strerror("Memory allocation failure in main.");
	read_input(data, &rooms);
	print_data(data, rooms); //Remove before submission
	system("leaks lem-in");
	exit(EXIT_SUCCESS);
	return (0);
}

//Program execution:
//./lem-in < maps/test.map
