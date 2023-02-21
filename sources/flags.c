/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:20:14 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/21 16:35:21 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** set_flags:
** - Activates flags depending on which have been entered on input.
*/

void	set_flags(t_flags *flags, char flag)
{
	if (flag == 'l')
		flags->lines = true;
	else if (flag == 'p')
		flags->paths = true;
	else if (flag == 's')
		flags->solutions = true;
	else if (flag == 'a')
		flags->ants = false;
	else if (flag == 'g')
		flags->graph = true;
	else if (flag == 'i')
		flags->input = false;
	else if (flag == 'r')
		flags->rooms = true;
	else
		clean_lem_in("Invalid flag.");
}

/*
** parse_flags:
** - Reads the input, activating the given flags.
*/

void	parse_flags(t_flags *flags, int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc == 2 && argv[1][i++] == '-')
	{
		while (argv[1][i])
		{
			set_flags(flags, argv[1][i]);
			i++;
		}
	}
	else
		clean_lem_in("Usage: ./lem-in -[flag] < [map]");
}
