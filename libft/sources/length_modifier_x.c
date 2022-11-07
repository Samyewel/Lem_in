/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_modifier_x.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:09:50 by swilliam          #+#    #+#             */
/*   Updated: 2022/09/09 12:42:20 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** length_modifier_x:
** - Handles the length of the given hexadecimal for when the 'x' / 'X'
**   format is specified.
*/

void	length_modifier_x(t_printf *flags)
{
	uintmax_t	x;

	x = 0;
	if (flags->h == 0 && flags->ell == 0)
		x = va_arg(flags->args, unsigned int);
	else if (flags->h == 1 && flags->ell == 0)
		x = (unsigned short)va_arg(flags->args, unsigned int);
	else if (flags->h == 2 && flags->ell == 0)
		x = (unsigned char)va_arg(flags->args, unsigned int);
	else if (flags->h == 0 && flags->ell == 1)
		x = va_arg(flags->args, unsigned long);
	else if (flags->h == 0 && flags->ell == 2)
		x = va_arg(flags->args, unsigned long long);
	else if (flags->j == 1)
		x = va_arg(flags->args, uintmax_t);
	else if (flags->z == 1)
		x = va_arg(flags->args, size_t);
	else
		ft_printf_error(flags, "Incompatible length modifier flags used with "
			"'x / X' format.");
	print_hexadecimal(flags, x);
}
