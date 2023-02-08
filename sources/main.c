/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:16:16 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/08 14:21:35 by sam              ###   ########.fr       */
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
	data->longest_path = 0;
	data->line_count = 0;
	data->best_solution = -1;
	data->finished = 0;
	data->ant_num = 0;
	data->starting_search = false;
	data->ending_search = false;
	data->solution = NULL;
	data->counter = 0;
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
	heads->solutions = NULL;
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
	print_data(data);
	heads->room = room_list_to_array(heads);
	if (!heads->room)
		ft_printf_strerror("Memory allocation failure in main");
	backtrack_rooms(data, heads);
	heads->path = path_list_to_array(heads);
	if (!heads->path)
		ft_printf_strerror("Memory allocation failure in main");
	//print_rooms(heads);
	backtrack_paths(data, heads);
	store_solution(data, heads);
	// calculate_path_usage_times(data);
	// ant_mover(heads, data);
	ft_printf("\nLine count = %d\n", data->line_count);
	clean_path_list(heads);
	if (DEBUG == true && LEAKS == true) // REMOVE BEFORE SUBMISSION
		system("leaks lem-in");
	exit(EXIT_SUCCESS);
	return (0);
}
