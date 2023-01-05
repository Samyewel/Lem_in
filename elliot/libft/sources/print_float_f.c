/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:40:29 by swilliam          #+#    #+#             */
/*   Updated: 2022/09/13 15:07:04 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_float_f_prefix(t_printf *flags)
{
	if (flags->sign == 1 && flags->plus)
		flags->total_length += write(flags->fd, "+", 1);
	else if (flags->sign == -1)
		flags->total_length += write(flags->fd, "-", 1);
}

/*
** print_float_f_left:
** - Handles the conversion for when no '-' flag is used.
** - Handles characters being printed to the left of the given input, therefore
**   aligning it to the right.
*/

static void	print_float_f_left(t_printf *flags, int f_length
, char *f_string)
{
	if (flags->space && flags->sign > -1 && !flags->plus)
	{
		flags->total_length += write(flags->fd, " ", 1);
		flags->width--;
	}
	if (flags->zero_padding && flags->sign != 0)
		print_float_f_prefix(flags);
	while (flags->width-- > f_length)
	{
		if (flags->zero_padding)
			flags->total_length += write(flags->fd, "0", 1);
		else
			flags->total_length += write(flags->fd, " ", 1);
	}
	if (!flags->zero_padding && flags->sign != 0)
		print_float_f_prefix(flags);
	flags->total_length += write(flags->fd, f_string, f_length);
}

/*
** print_float_f_right:
** - Handles the conversion for when the '-' flag is used.
** - Handles characters being printed to the right of the given input, therefore
**   aligning it to the left.
*/

static void	print_float_f_right(t_printf *flags, int f_length
, char *f_string)
{
	if (flags->space && flags->sign > -1 && !flags->plus)
	{
		flags->total_length += write(flags->fd, " ", 1);
		flags->width--;
	}
	if (flags->sign)
		print_float_f_prefix(flags);
	flags->total_length += write(flags->fd, f_string, f_length);
	while (flags->width-- > f_length)
		flags->total_length += write(flags->fd, " ", 1);
}

/*
** print_f_float:
** - Uses float_f_rounding to calculate and create a string containing the float
**   converted into an integer, then into characters, with its decimal point
**   manually inserted.
** - If float is 0.0, we need to manually add the remaining five trailing 0s.
** - If a '-' flag is used, the conversion will align the string to the left,
**   otherwise it will align to the right.
*/

void	print_float_f(t_printf *flags, long double f)
{
	char		*f_string;
	long double	f_rounded;
	int			f_length;

	if (1 / f >= 0.0)
		flags->sign = 1;
	else
		flags->sign = -1;
	f_rounded = float_f_rounding(flags, f);
	f_string = float_f_dtostr(flags, f_rounded);
	if (f_string == NULL)
		return ;
	f_length = ft_strlen(f_string);
	flags->width -= (flags->sign < 0 || (flags > 0 && flags->plus));
	if (flags->dash)
		print_float_f_right(flags, f_length, f_string);
	else
		print_float_f_left(flags, f_length, f_string);
	if (f_string != NULL)
		ft_strdel(&f_string);
}
