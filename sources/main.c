/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:16:16 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/07 12:53:47 by swilliam         ###   ########.fr       */
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
	heads->rooms = NULL;
	heads->room_array = NULL;
	heads->paths = NULL;
	heads->path_array = NULL;
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
	heads->room_array =	room_list_to_array(heads);
	backtrack_rooms(data, heads);
	heads->path_array = path_list_to_array(heads);
	if (!heads->path_array)
		ft_printf_strerror("Memory allocation failure in \
		path_list_to_array");
	backtrack_paths(data, heads);
	print_rooms(heads);
	ft_printf("Storing solution...\n");
	store_solution(data, heads);
	ft_printf("Calculating usage time...\n");
	calculate_path_usage_times(data);
	ft_printf("Printing...\n");
	ant_mover(heads, data);
	ft_printf("\nLine count = %d\n", data->line_count);
	if (DEBUG == true && LEAKS == true) // REMOVE BEFORE SUBMISSION
		system("leaks lem-in");
		//system("leaks lem-in | grep 'leaks for'");
	clean_paths(heads);
	exit(EXIT_SUCCESS);
	return (0);
}
