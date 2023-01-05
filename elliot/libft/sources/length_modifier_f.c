/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_modifier_f.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:16:43 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/03 15:12:06 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** length_modifier_f:
** - Handles the length of the given float for when the 'f' format is
**   specified.
** - Prints double rounded and converted to decimal notation ([-]ddd.ddd).
*/

void	length_modifier_f(t_printf *flags)
{
	double	f;

	f = 0;
	if ((flags->ell == 0 || flags->ell == 1) && flags->large_ell == 0)
		f = va_arg(flags->args, double);
	else if (flags->ell == 0 && flags->large_ell == 1)
		f = va_arg(flags->args, long double);
	else
		ft_printf_error(flags, "Incompatible length modifier flags used with "
			"'f / F' format.");
	print_float_f(flags, f);
}
