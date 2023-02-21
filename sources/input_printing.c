/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:52:48 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/21 16:42:23 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** store_input:
** - Stores the current line being read into an array so that it can be
**   after error checks are completed.
*/

void	store_input(t_data *data, char *line, int line_n)
{
	if (!data->input)
	{
		data->input = (char **)malloc(sizeof(char *) * (MAX_SIZE * 2));
		if (!data->input)
			clean_lem_in("Memory allocation failure in store_input.");
	}
	data->input[line_n] = ft_strdup(line);
	if (!data->input[line_n])
		clean_lem_in("Memory allocation failure in store_input");
}

/*
** print_input:
** - Prints the input map.
*/

void	print_input(t_heads *heads, t_data *data)
{
	int	i;

	i = -1;
	if (!data->input)
		clean_lem_in("No input stored.");
	if (heads->flags->input == true)
	{
		while (++i < (MAX_SIZE * 2) && data->input[i])
			ft_putendl(data->input[i]);
	}
	ft_printf("\n");
}
