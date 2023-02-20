/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:16:16 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/20 11:55:39 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_flags(t_data *data, char flag)
{
	if (flag == 'l')
		data->lines = true;
	if (flag == 'p')
		data->print_paths = true;
}

void	parse_flags(t_data *data, int argc, char **argv)
{
	int i;

	i = 0;
	if (argc == 2 && argv[1][i++] == '-')
	{
		if (argv[1][i] && ft_strchr("l", argv[1][i]))
		{
			while (argv[1][i])
			{
				init_flags(data, argv[1][i]);
				i++;
			}
		}
	}
}

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
	data->print_paths = false;
	data->lines = false;
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
** -
*/

int	main(int argc, char **argv)
{
	t_heads	*heads;
	t_data	*data;

	data = NULL;
	heads = NULL;
	data = initialise_data(data);
	heads = initialise_heads(data, heads);
	if (!data || !heads)
		clean_lem_in("Memory allocation failure in main.");
	if (argc > 1)
		parse_flags(data, argc, argv);
	read_input(data, heads);
	edmonds_karp(data, heads);
	backtrack_paths(data, heads);
	store_solution(data, heads);
	printer(heads, data);
	if (data->lines == true)
		ft_printf("\nLine count = %d\n", data->line_count);
	if (DEBUG == true && LEAKS == true) // REMOVE BEFORE SUBMISSION
		system("leaks lem-in");
	exit(EXIT_SUCCESS);
	return (0);
}
