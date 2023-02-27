/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:16:16 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/22 15:27:37 by swilliam         ###   ########.fr       */
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
	data->bfs_path = 0;
	data->starting_search = false;
	data->start_found = false;
	data->ending_search = false;
	data->end_found = false;
	data->solution = NULL;
	data->counter = 0;
	data->input = NULL;
	data->links_started = false;
	data->last_link_0 = NULL;
	data->last_link_1 = NULL;
	data->print_paths = false;
	data->lines = false;
	return (data);
}

/*
** initialise_input_flags:
** - Initialises the struct used for the flags to modify the output.
*/

static t_flags	*initialise_input_flags(t_flags *flags)
{
	flags = (t_flags *)malloc(sizeof(t_flags));
	if (!flags)
		return (NULL);
	flags->input = true;
	flags->ants = true;
	flags->rooms = false;
	flags->lines = false;
	flags->paths = false;
	flags->graph = false;
	flags->solutions = false;
	return (flags);
}

/*
** initialise_heads:
** - Initialises a struct containing the heads of each list used during the
**   program.
*/

static t_heads	*initialise_heads(t_data *data, t_heads *heads, t_flags *flags)
{
	heads = (t_heads *)malloc(sizeof(t_heads));
	if (!heads)
		return (NULL);
	heads->data = data;
	heads->flags = flags;
	heads->room = NULL;
	heads->path = NULL;
	heads->solution = NULL;
	heads->residual = NULL;
	heads->stored = NULL;
	heads->parent = NULL;
	heads->ants = NULL;
	return (heads);
}

/*
** lem-in:
** - Parses given input flags to determine what data is printed on output.
** - Parses input to store rooms, links and ant count.
** - Utilises the Edmonds Karp algorithm to store augmenting paths from
**   the start to end nodes.
** - Backtracks the paths and stores them in a solution struct in ascending
**   length order.
** - Calculates how much each path can be used to determine the shortest
**   amount of turns traversal will take.
** - Moves ants from start to end using stored paths and their usages.
** - Prints total amount of lines used during printing.
*/

int	main(int argc, char **argv)
{
	t_data	*data;
	t_flags	*flags;
	t_heads	*heads;

	data = NULL;
	flags = NULL;
	heads = NULL;
	data = initialise_data(data);
	flags = initialise_input_flags(flags);
	heads = initialise_heads(data, heads, flags);
	if (!data || !heads || !flags)
		clean_lem_in("Memory allocation failure in main.");
	if (argc > 1)
		parse_flags(flags, argc, argv);
	read_input(data, heads);
	edmonds_karp(data, heads);
	backtrack_paths(data, heads);
	store_solution(data, heads);
	printer(heads, data);
	if (flags->lines == true)
		ft_printf("\nLine count = %d\n", data->line_count);
	exit(EXIT_SUCCESS);
	return (0);
}
