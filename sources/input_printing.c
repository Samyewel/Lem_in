/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:52:48 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/20 14:07:50 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	store_input(t_data *data, char *line, int line_n)
{
	if (!data->input)
	{
		data->input = (char **)malloc(sizeof(char *) * MAX_SIZE);
		if (!data->input)
			clean_lem_in("Memory allocation failure in store_input.");
	}
	data->input[line_n] = ft_strdup(line);
	if (!data->input[line_n])
		clean_lem_in("Memory allocation failure in store_input");
}

void	print_input(t_heads *heads, t_data *data)
{
	int	i;

	i = -1;
	if (!data->input)
		clean_lem_in("No input stored.");
	if (heads->flags->input == true)
	{
		while (++i < MAX_SIZE && data->input[i])
			ft_putendl(data->input[i]);
	}
}
