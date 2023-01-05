/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_modifier_s.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:39:09 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/03 15:12:55 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** length_modifier_s:
** - Prints a string.
*/

void	length_modifier_s(t_printf *flags)
{
	char	*str;

	if (flags->format == 's' && flags->ell == 0)
	{
		str = va_arg(flags->args, char *);
		print_string(flags, str);
	}
	else
		ft_printf_error(flags, "Incompatible length modifier flags used with "
			"'s / S' format.");
}
