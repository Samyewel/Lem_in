/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:16:16 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/25 16:35:17 by sam              ###   ########.fr       */
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
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_printf_strerror("Memory allocation failure in initialise_data");
	data->ant_count = 0;
	data->room_count = 0;
	data->longest_path = 0;
	data->max_flow = 0;
	data->finished = 0;
	data->ant_num = 0;
	data->starting_search = false;
	data->ending_search = false;
	return (data);
}

/*
** initialise_heads:
** - Initialises a struct containing the heads of each list used during the
**   program.
*/

t_heads	*initialise_heads(t_heads *heads)
{
	heads = (t_heads *)malloc(sizeof(t_heads));
	if (!heads)
		ft_printf_strerror("Memory allocation failure in initialise_heads");
	heads->rooms = NULL;
	heads->queue = NULL;
	heads->paths = NULL;
	heads->ants = NULL;
	heads->stack = NULL;
	return (heads);
}

/*
** lem-in:
** -
*/

int	main(void)
{
	t_heads	*heads;
	t_data	*data;

	data = NULL;
	heads = NULL;
	data = initialise_data(data);
	heads = initialise_heads(heads);
	if (!data || !heads)
		ft_printf_strerror("Memory allocation failure in main.");
	read_input(data, heads);
	if (DEBUG == true && ROOMS == true)
		print_rooms(&heads->rooms);
	print_data(data);
	calculate_flow(heads, data);
	if (DEBUG == true && LEAKS == true)
		system("leaks lem-in");
		//system("leaks lem-in | grep 'leaks for'");
	clean_paths(heads);
	exit(EXIT_SUCCESS);
	return (0);
}
