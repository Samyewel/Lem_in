/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:09:41 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/16 16:13:10 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** ft_printf_error:
** - Deletes all of the already printed text and prints an error message
**   in it's place.
*/

void	ft_printf_error(t_printf *flags, char *error_message)
{
	int	del_len;

	del_len = flags->parsing_length + flags->total_length;
	if (error_message)
	{
		while (del_len-- > 0)
			ft_putstr("\b \b");
		ft_dprintf(2, "\e[4;31m[ERROR]\e[0m \e[4;37m%s\n\e[0m", error_message);
	}
	return (exit(EXIT_FAILURE));
}

void	ft_printf_strerror(char *error_message)
{
	if (error_message)
		ft_dprintf(2, "\n\e[4;31m[ERROR]\e[0m \e[4;37m%s\n\e[0m", error_message);
	return (exit(EXIT_FAILURE));
}
