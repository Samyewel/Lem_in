/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_modifier_u.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:13:40 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/03 15:13:43 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** length_modifier_u:
** - Handles the length of the given decimal for when the 'u' / 'U'
**   format is specified.
*/

void	length_modifier_u(t_printf *flags)
{
	uintmax_t	u;

	u = 0;
	if (flags->format == 'u' && flags->h == 0 && flags->ell == 0)
		u = va_arg(flags->args, unsigned int);
	else if (flags->format == 'u' && flags->h == 1 && flags->ell == 0)
		u = (unsigned short) va_arg(flags->args, unsigned int);
	else if (flags->format == 'u' && flags->h == 2 && flags->ell == 0)
		u = (unsigned char) va_arg(flags->args, unsigned int);
	else if ((flags->format == 'u' && flags->h == 0 && flags->ell == 1)
		|| (flags->format == 'U' && flags->h == 0 && flags->ell == 0))
		u = va_arg(flags->args, unsigned long);
	else if (flags->format == 'u' && flags->h == 0 && flags->ell == 2)
		u = va_arg(flags->args, unsigned long long);
	else if (flags->format == 'u' && flags->j == 1)
		u = va_arg(flags->args, uintmax_t);
	else if (flags->format == 'u' && flags->z == 1)
		u = va_arg(flags->args, size_t);
	else
		ft_printf_error(flags, "Incompatible length modifier flags used with "
			"'u / U' format.");
	print_decimal(flags, u);
}
