/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:31:46 by sam               #+#    #+#             */
/*   Updated: 2022/09/01 16:18:26 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** initialise_reading_values:
** - values specifially used for the entire reading process are initialised
**   seperately from our flags as they are freed at seperate times.
*/

t_printf	*initialise_reading_values(t_printf *flags, int fd)
{
	flags->parsing_length = 0;
	flags->total_length = 0;
	flags->fd = fd;
	return (flags);
}

/*
** initialise_flags:
** - Each flag in our struct is treated like a boolean, so that if it is not
**   found, it remains as 0 (false), when found it is incremented by 1 (true).
*/

t_printf	*initialise_flags(t_printf *flags)
{
	flags->precision_specified = 0;
	flags->zero_padding = 0;
	flags->apostrophe = 0;
	flags->large_ell = 0;
	flags->precision = 0;
	flags->is_zero = 0;
	flags->percent = 0;
	flags->dollar = 0;
	flags->format = '0';
	flags->period = 0;
	flags->space = 0;
	flags->width = 0;
	flags->dash = 0;
	flags->hash = 0;
	flags->plus = 0;
	flags->sign = 0;
	flags->star = 0;
	flags->ell = 0;
	flags->h = 0;
	flags->j = 0;
	flags->z = 0;
	return (flags);
}

/*
** flag_check:
** - Ensures there are a valid number of flags used.
*/

static int	flag_check(t_printf *flags)
{
	if (flags->apostrophe > 1 || flags->large_ell > 1 || flags->dollar > 1
		|| flags->period > 1 || flags->dash > 1 || flags->hash > 1
		|| flags->star > 1 || flags->ell > 2 || flags->h > 2
		|| flags->j > 1 || flags->z > 1)
		return (0);
	return (1);
}

/*
** check_width_precision:
** - Accurately reads whether digits read are to be given as width or
**   precision.
** - If an asterisk is written, the next argument is given as width or
**   precision.
*/

static void	check_width_precision(t_printf *flags, const char *input, int i)
{
	if (input[i] == '.' && !flags->precision_specified)
	{
		if (ft_isdigit(input[i + 1]))
			flags->precision = ft_atoi(&input[i + 1]);
		else if (input[i + 1] == '*')
			flags->precision = va_arg(flags->args, int);
		flags->precision_specified = 1;
	}
	else if (input[i - 1] != '.' && ft_isdigit(input[i]) && !flags->width)
	{
		if (input[i - 1] != '0')
			flags->width = ft_atoi(&input[i]);
		else if (input[i] == '*')
			flags->width = va_arg(flags->args, int);
	}
}

/*
**	update_flags:
**  - If a flag is provided, the data in our struct is incremented by 1 (from 0)
**    to specify that it exists (true).
*/

int	update_flags(t_printf *flags, const char *input, int i)
{
	check_width_precision(flags, input, i);
	if (input[i] == '0' && !ft_isdigit(input[i - 1]) && input[i - 1] != '.')
		flags->zero_padding = 1;
	flags->apostrophe += input[i] == 39;
	flags->large_ell += input[i] == 'L';
	flags->dollar += input[i] == '$';
	flags->period += input[i] == '.';
	flags->space += input[i] == ' ';
	flags->dash += input[i] == '-';
	flags->hash += input[i] == '#';
	flags->plus += input[i] == '+';
	flags->star += input[i] == '*';
	flags->ell += input[i] == 'l';
	flags->h += input[i] == 'h';
	flags->j += input[i] == 'j';
	flags->z += input[i] == 'z';
	return (flag_check(flags));
}
