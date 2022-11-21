/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:16:16 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/21 16:20:25 by swilliam         ###   ########.fr       */
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
	data = initialise_data(data);
	links = (t_links *)malloc(sizeof(t_links));
	if (!links || !data)
	{
		ft_printf("Error during memory allocation in %s on line %d.", __func__, __LINE__);
		exit(EXIT_FAILURE);
	}
	read_input(data, &rooms, links);
	print_data(data, rooms, links); //for testing purposes
	system("leaks lem-in");
	exit(EXIT_SUCCESS);
	return (0);
}

//Program execution:
//./lem-in < maps/test.map