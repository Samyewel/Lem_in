/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_modifier_o.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:39:03 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/03 15:14:00 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** length_modifier_o:
** - Handles the length of the given octal for when the 'o' / 'O' format is
**   specified.
*/

void	length_modifier_o(t_printf *flags)
{
	uintmax_t	o;

	o = 0;
	if (flags->format == 'o' && flags->h == 0 && flags->ell == 0)
		o = va_arg(flags->args, unsigned int);
	else if (flags->format == 'o' && flags->h == 1 && flags->ell == 0)
		o = (unsigned short) va_arg(flags->args, unsigned int);
	else if (flags->format == 'o' && flags->h == 2 && flags->ell == 0)
		o = (unsigned char) va_arg(flags->args, unsigned int);
	else if ((flags->format == 'o' && flags->h == 0 && flags->ell == 1)
		|| (flags->format == 'O' && flags->h == 0 && flags->ell == 0))
		o = va_arg(flags->args, unsigned long);
	else if (flags->format == 'o' && flags->h == 0 && flags->ell == 2)
		o = va_arg(flags->args, unsigned long long);
	else
		ft_printf_error(flags, "Incompatible length modifier flags used with "
			"'o / O' format.");
	print_octal(flags, o);
}
