/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:16:16 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/12 18:32:09 by swilliam         ###   ########.fr       */
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
	heads->rooms_head = NULL;
	heads->queue_head = NULL;
	heads->paths_head = NULL;
	heads->ants_head = NULL;
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
		print_rooms(&heads->rooms_head);
	if (DEBUG == true && EXTRA == true)
		print_data(data);
	if (find_max_flow(heads, data) > 0)
		ft_printf("");
	if (DEBUG == true && LEAKS == true)
		system("leaks lem-in | grep 'leaks for'");
	exit(EXIT_SUCCESS);
	return (0);
}
