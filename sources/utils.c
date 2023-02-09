/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:52:24 by egaliber          #+#    #+#             */
/*   Updated: 2023/02/07 18:52:52 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	ft_is_dash(char *str)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
			counter++;
		i++;
	}
	return (counter);
}

int	ft_is_space(char *str)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			counter++;
		i++;
	}
	return (counter);
}
