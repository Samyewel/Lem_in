/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_modifier_di.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:39:22 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/22 14:11:28 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** length_modifier_di:
** - Handles the length of the given integer for when the 'd' / 'D' / 'i'
**   format is specified.
*/

void	length_modifier_di(t_printf *flags)
{
	intmax_t	d;

	if (flags->format == 'i')
		flags->format = 'd';
	d = 0;
	if (flags->format == 'd' && flags->h == 0 && flags->ell == 0)
		d = va_arg(flags->args, int);
	else if (flags->format == 'd' && flags->h == 1 && flags->ell == 0)
		d = (short) va_arg(flags->args, int);
	else if (flags->format == 'd' && flags->h == 2 && flags->ell == 0)
		d = (signed char) va_arg(flags->args, int);
	else if ((flags->format == 'd' && flags->h == 0 && flags->ell == 1)
		|| (flags->format == 'D' && flags->h == 0 && flags->ell == 0))
		d = va_arg(flags->args, long);
	else if (flags->format == 'd' && flags->h == 0 && flags->ell == 2)
		d = va_arg(flags->args, long long);
	else if (flags->j == 1)
		d = va_arg(flags->args, intmax_t);
	else if (flags->z == 1)
		d = va_arg(flags->args, size_t);
	else
		ft_printf_error(flags, "Incompatible length modifier flags used with "
			"'d / i' format.");
	print_integer(flags, d);
}
