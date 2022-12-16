/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:16:16 by swilliam          #+#    #+#             */
/*   Updated: 2022/12/16 17:07:18 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** initialise_data:
** - Allocates the struct used to store data that associated with the
**   functionality of the project.
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

	data = NULL;
	rooms = NULL;
	data = initialise_data(data);
	if (!data)
		ft_printf_strerror("Memory allocation failure in main.");
	read_input(data, &rooms);
	if (DEBUG == true)
		print_data(data, rooms); // Remove before submission
	if (find_max_flow(rooms) > 0)
		ft_printf("");
	if (DEBUG == true)
		system("leaks lem-in | grep 'leaks for'");
	exit(EXIT_SUCCESS);
	return (0);
}
