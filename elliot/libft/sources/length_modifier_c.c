/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_modifier_c.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:05:15 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/03 15:09:44 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** length_modifier_c:
** - Handles the length of the given input for when the 'c' format is
**   specified.
*/

void	length_modifier_c(t_printf *flags)
{
	char	c;

	if (flags->format == 'c' && flags->ell == 0)
	{
		c = (unsigned char) va_arg(flags->args, int);
		print_char(flags, c);
	}
	else
		ft_printf_error(flags, "Incompatible length modifier flags used with "
			"'c' format.");
}
