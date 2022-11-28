/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:16:16 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/28 12:11:18 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** initialise_data:
** -
*/

t_data	*initialise_data(t_data *data)
{
	if (!(data))
		data = (t_data *)malloc(sizeof(t_data));
	data->ant_count = 0;
	data->starting_search = false;
	data->ending_search = false;
	return (data);
}

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
