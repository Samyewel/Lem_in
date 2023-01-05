/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_float_f_utilities.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:23:08 by swilliam          #+#    #+#             */
/*   Updated: 2022/09/15 16:52:37 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** float_f_create_suffix:
** - The prefix is created by converting the double into an integer, thus
**   removing the decimal places.
** - If the whole number is zero, it is manually placed.
** - The decimal point is manually added after the whole number if
**   necessary.
*/

static char	*float_f_create_prefix(t_printf *flags, long double f)
{
	char	*prefix;
	char	*temp;

	if (f > -1.0 && f < 1.0)
		prefix = ft_strdup("0");
	else
		prefix = ft_printf_signed_itoa((intmax_t)f * flags->sign);
	if (prefix == NULL)
		return (NULL);
	if ((flags->precision_specified && (flags->precision || flags->hash))
		|| (!flags->precision_specified))
	{
		temp = ft_strdup(prefix);
		ft_strdel(&prefix);
		prefix = ft_strjoin(temp, ".");
		ft_strdel(&temp);
	}
	return (prefix);
}

/*
** float_f_create_suffix:
** - The suffix is created using the decimal places converted to a whole
**   number.
** - The suffix is padded with zeroes if needed, as when it is converted
**   into an int, leading zeroes are not included.
*/

static char	*float_f_create_suffix(intmax_t f_int, size_t len)
{
	char	*suffix;
	char	*temp1;
	char	*temp2;

	suffix = ft_printf_signed_itoa(f_int);
	if (suffix == NULL)
		return (NULL);
	if (ft_strlen(suffix) < len)
	{
		temp1 = ft_strnew(len - ft_strlen(suffix));
		while (len-- > ft_strlen(suffix))
			temp1[len - ft_strlen(suffix)] = '0';
		temp2 = ft_strdup(suffix);
		ft_strdel(&suffix);
		suffix = ft_strjoin(temp1, temp2);
		ft_strdel(&temp1);
		ft_strdel(&temp2);
	}
	return (suffix);
}

/*
** float_f_itodstr:
** - The double is split into two strings: the whole number (prefix)
**   and the trailing decimal places.
** - The prefix and suffix are joined together.
*/

static char	*float_f_ditostr(t_printf *flags, long double f,
intmax_t f_int, size_t len)
{
	char	*prefix;
	char	*suffix;
	char	*final_string;

	prefix = float_f_create_prefix(flags, f);
	if (!prefix)
		return (NULL);
	if (flags->precision_specified && !flags->precision)
		return (prefix);
	suffix = float_f_create_suffix(f_int, len);
	if (!suffix)
		return (NULL);
	final_string = ft_strjoin(prefix, suffix);
	if (!final_string)
		return (NULL);
	ft_strdel(&prefix);
	ft_strdel(&suffix);
	return (final_string);
}

/*
** float_f_dtostr:
** - Multiplies the input to the correct power, then splits it
**   for conversion purposes.
*/

char	*float_f_dtostr(t_printf *flags, long double f)
{
	int			precision_count;
	long double	f_powered;
	size_t		len;

	if (flags->precision_specified && flags->precision <= 18)
		len = flags->precision;
	if (flags->precision_specified && flags->precision > 18)
		len = 18;
	else
		len = 6;
	precision_count = len;
	f_powered = f - (intmax_t)f;
	while (precision_count--)
		f_powered *= 10.0;
	f_powered *= flags->sign;
	return (float_f_ditostr(flags, f, (intmax_t)f_powered, len));
}

/*
** float_f_rounding:
** - Rounds a number up to the decimal point given as precision, or
**   6 by default.
*/

long double	float_f_rounding(t_printf *flags, long double f)
{
	int			precision_count;
	long double	rounding;

	rounding = 0.5;
	rounding *= flags->sign;
	if (flags->precision_specified && flags->precision <= 19)
		precision_count = flags->precision;
	if (flags->precision_specified && flags->precision > 19)
		precision_count = 19;
	else
		precision_count = 6;
	while (precision_count--)
		rounding /= 10.0;
	return (f + rounding);
}
