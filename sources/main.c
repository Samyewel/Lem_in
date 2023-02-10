/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:16:16 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/10 11:59:14 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** initialise_data:
** - Allocates the struct used to store data that associated with the
**   functionality of the project.
*/

static t_data	*initialise_data(t_data *data)
{
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->ant_count = 0;
	data->room_count = 0;
	data->path_count = 0;
	data->line_count = 0;
	data->finished = 0;
	data->ant_num = 0;
	data->starting_search = false;
	data->start_found = false;
	data->ending_search = false;
	data->solution = NULL;
	data->counter = 0;
	data->links_started = false;
	data->last_link_0 = NULL;
	data->last_link_1 = NULL;
	return (data);
}

/*
** initialise_heads:
** - Initialises a struct containing the heads of each list used during the
**   program.
*/

static t_heads	*initialise_heads(t_data *data, t_heads *heads)
{
	heads = (t_heads *)malloc(sizeof(t_heads));
	if (!heads)
		return (NULL);
	heads->data = data;
	heads->room_list = NULL;
	heads->room = NULL;
	heads->path_list = NULL;
	heads->path = NULL;
	heads->solution = NULL;
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
	heads = initialise_heads(data, heads);
	if (!data || !heads)
		ft_printf_strerror("Memory allocation failure in main.");
	read_input(data, heads);
	room_list_to_array(heads);
	backtrack_rooms(data, heads);
	path_list_to_array(heads);
	backtrack_paths(data, heads);
	store_solution(data, heads);
	calculate_usage(data, heads, data->solution);
	print_solution(data->solution);
	ant_mover(heads, data);
	ft_printf("\nLine count = %d\n", data->line_count);
	if (DEBUG == true && LEAKS == true) // REMOVE BEFORE SUBMISSION
		system("leaks lem-in");
	exit(EXIT_SUCCESS);
	return (0);
}
