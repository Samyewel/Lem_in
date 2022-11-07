/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_octal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:45:42 by swilliam          #+#    #+#             */
/*   Updated: 2022/09/13 15:06:03 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** octal_left_padding:
** - Handles the padding necessary padding for when printing to the left
**   of the octal number.
*/

static void	octal_left_padding(t_printf *flags, int o_length, int prefix)
{
	char	padding;

	if (flags->zero_padding && !flags->precision_specified)
		padding = '0';
	else
		padding = ' ';
	if (flags->precision_specified && flags->precision > (o_length + prefix))
	{
		while (flags->width-- > flags->precision)
		{
			if (flags->width != flags->precision)
				flags->total_length += write(flags->fd, &padding, 1);
			else
				flags->total_length += write(flags->fd, " ", 1);
		}
	}
	else
		while (flags->width-- > (o_length + prefix))
			flags->total_length += write(flags->fd, &padding, 1);
}

/*
** print_octal_left:
** - Handles the conversion for when no '-' flag is used.
** - Prints the respective padding to the left of the converted octal number,
**   therefore aligning it to the right.
*/

static void	print_octal_left(t_printf *flags, uintmax_t o, int o_length
, char *utoa_res)
{
	int	i;
	int	prefix;

	i = 0;
	prefix = 0;
	prefix += (flags->hash && (o_length == 0 || (o != 0 && o_length > 0)));
	octal_left_padding(flags, o_length, prefix);
	if (prefix)
	{
		flags->total_length += write(1, "0", 1);
		flags->width--;
	}
	if (flags->zero_padding && !flags->precision_specified)
	{
		while (flags->width-- > (o_length + prefix + i++))
			flags->total_length += write(flags->fd, "0", 1);
	}
	if (flags->precision_specified && flags->precision > (o_length + prefix))
	{
		while ((o_length + i++) < flags->precision - prefix)
			flags->total_length += write(flags->fd, "0", 1);
	}
	flags->total_length += write(flags->fd, utoa_res, o_length);
}
/*
** print_octal_right:
** - Handles the conversion for when the '-' flag is used.
** - Prints the respective padding to the right of the converted octal number,
**   therefore aligning it to the left.
*/

static void	print_octal_right(t_printf *flags, uintmax_t o, int o_length
, char *utoa_res)
{
	int	i;
	int	prefix;

	i = 0;
	prefix = 0;
	prefix += (flags->hash && (o_length == 0 || (o != 0 && o_length > 0)));
	if (prefix)
		flags->total_length += write(1, "0", 1);
	if (flags->precision > (o_length + i + prefix))
	{
		while (o_length + prefix + i < flags->precision)
		{
			flags->total_length += write(flags->fd, "0", 1);
			i++;
		}
	}
	flags->total_length += write(flags->fd, utoa_res, o_length);
	while (flags->width-- > o_length + i + prefix)
			flags->total_length += write(flags->fd, " ", 1);
}
/*
** print_octal:
** - If the input value is 0 and no precision is specified, the width is
**   handled seperately from other calculations.
** - If a '-' flag is used, the conversion will align the string to the left,
**   otherwise it will align to the right.
*/

void	print_octal(t_printf *flags, uintmax_t o)
{
	char	*utoa_res;
	int		o_length;

	utoa_res = ft_printf_utoa_base(flags, o, 8);
	o_length = ft_strlen(utoa_res);
	if (flags->precision_specified && flags->precision == 0)
		o_length = 0;
	if (flags->dash)
		print_octal_right(flags, o, o_length, utoa_res);
	else
		print_octal_left(flags, o, o_length, utoa_res);
	ft_strdel(&utoa_res);
}
