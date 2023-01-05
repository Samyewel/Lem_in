/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:17:12 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/03 15:31:09 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** print_char_left:
** - Handles the conversion for when no '-' flag is used.
** - Prints the respective padding to the left of the converted character,
**   therefore aligning it to the right.
*/

static void	print_char_left(t_printf *flags, char c)
{
	char	padding;

	if (flags->zero_padding)
		padding = '0';
	else
		padding = ' ';
	while (flags->width-- > 1)
		flags->total_length += write(flags->fd, &padding, 1);
	flags->total_length += write(flags->fd, &c, 1);
}

/*
** print_char_right:
** - Handles the conversion for when the '-' flag is used.
** - Prints the respective padding to the right of the converted character,
**   therefore aligning it to the left.
*/

static void	print_char_right(t_printf *flags, char c)
{
	flags->total_length += write(flags->fd, &c, 1);
	while (flags->width-- > 1)
		flags->total_length += write(flags->fd, " ", 1);
}

/*
** print_char:
** - Prints a character aligned to the left or right depending on if the
**   '-' flag is used or not.
*/

void	print_char(t_printf *flags, char c)
{
	if (flags->dash)
		print_char_right(flags, c);
	else
		print_char_left(flags, c);
}
