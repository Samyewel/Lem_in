/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:46:59 by swilliam          #+#    #+#             */
/*   Updated: 2022/09/05 13:43:46 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** print_string_left:
** - Handles the conversion for when no '-' flag is used.
** - Prints the respective padding to the left of the converted octal number,
**   therefore aligning it to the right.
*/

static void	print_string_left(t_printf *flags, char *str, int s_length)
{
	while (flags->width-- > s_length)
			flags->total_length += write(flags->fd, " ", 1);
	flags->total_length += write(flags->fd, str, s_length);
}

/*
** print_string_right:
** - Handles the conversion for when the '-' flag is used.
** - Prints the respective padding to the right of the converted string,
**   therefore aligning it to the left.
*/

static void	print_string_right(t_printf *flags, char *str, int s_length)
{
	flags->total_length += write(flags->fd, str, s_length);
	while (flags->width-- > s_length)
		flags->total_length += write(flags->fd, " ", 1);
}

/*
** print_string:
** - If the input string is empty, "(null)" is manually printed.
** - If a '-' flag is used, the conversion will align the string to the left,
**   otherwise it will align to the right.
*/

void	print_string(t_printf *flags, char *str)
{
	int		s_length;

	if (str == NULL)
		str = "(null)";
	s_length = ft_strlen(str);
	if (flags->precision_specified && (flags->precision <= s_length))
		s_length = flags->precision;
	if (str[0] == '\0' && !flags->precision_specified)
	{
		while (flags->width--)
			flags->total_length += write(flags->fd, " ", 1);
		return ;
	}
	if (flags->dash)
		print_string_right(flags, str, s_length);
	else
		print_string_left(flags, str, s_length);
}
