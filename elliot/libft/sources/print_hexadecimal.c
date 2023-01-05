/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexadecimal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:18:43 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/28 13:54:32 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** hex_prefix:
** - Prints the respective prefix for the number given depending on if the 'x'
**   or 'X' flag is used.
** - If the input is a pointer address, then we print an '0x' prefix.
*/

static void	hex_prefix(t_printf *flags, unsigned long long x)
{
	if (x != 0 || flags->format == 'p')
	{
		if (flags->format == 'x' || flags->format == 'p')
			flags->total_length += write(flags->fd, "0x", 2);
		else if (flags->format == 'X')
			flags->total_length += write(flags->fd, "0X", 2);
	}
}

/*
** print_hex_left:
** - Handles the conversion for when no '-' flag is used.
** - Prints the respective padding to the left of the converted hexadecimal,
**   therefore aligning it to the right.
*/

static void	print_hex_left(t_printf *flags, unsigned long long x, int x_length,
char *utoa_res)
{
	int		prefix;

	prefix = 0;
	if (flags->precision_specified && flags->precision > x_length)
		x_length = flags->precision;
	if ((flags->hash && x != 0) || flags->format == 'p')
		prefix = 2;
	if ((!flags->zero_padding && !flags->precision_specified)
		|| flags->precision_specified)
	{
		while (flags->width-- > (x_length + prefix))
			flags->total_length += write(flags->fd, " ", 1);
	}
	if ((flags->hash && x != 0) || flags->format == 'p')
		hex_prefix(flags, x);
	if (flags->zero_padding && !flags->precision_specified)
		while (flags->width-- > x_length + prefix)
			flags->total_length += write(flags->fd, "0", 1);
	if (flags->precision_specified)
		while (x_length-- > (int)ft_strlen(utoa_res))
			flags->total_length += write(flags->fd, "0", 1);
	flags->total_length += write(flags->fd, utoa_res, ft_strlen(utoa_res));
}

/*
** print_hex_right:
** - Handles the conversion for when the '-' flag is used.
** - Prints the respective padding to the right of the converted hexadecimal,
**   therefore aligning it to the left.
*/

static void	print_hex_right(t_printf *flags, unsigned long long x, int x_length,
char *utoa_res)
{
	int	i;
	int	prefix;

	i = 0;
	prefix = 0;
	if ((flags->hash && x != 0) || flags->format == 'p')
	{
		hex_prefix(flags, x);
		prefix = 2;
	}
	while (x_length + i < flags->precision)
	{
		flags->total_length += write(flags->fd, "0", 1);
		i++;
	}
	flags->total_length += write(flags->fd, utoa_res, ft_strlen(utoa_res));
	while (flags->width-- > x_length + i + prefix)
		flags->total_length += write(flags->fd, " ", 1);
}

/*
** print_hexadecimal:
** - Prints the given input as a hexidecimal value.
** - Also takes a pointer address as an input to be printed with a prefix.
** - If a '-' flag is used, the conversion will align the string to the left,
**   otherwise it will align to the right.
*/

void	print_hexadecimal(t_printf *flags, unsigned long long x)
{
	char	*utoa_res;
	int		x_length;

	if (x == 0 && flags->precision_specified && !flags->precision)
	{
		while (flags->width--)
			flags->total_length += write(flags->fd, " ", 1);
		return ;
	}
	utoa_res = ft_printf_utoa_base(flags, x, 16);
	x_length = ft_strlen(utoa_res);
	if (flags->dash)
		print_hex_right(flags, x, x_length, utoa_res);
	else
		print_hex_left(flags, x, x_length, utoa_res);
	ft_strdel(&utoa_res);
}
