/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_modifier_p.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:11:01 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/03 14:17:44 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** length_modifier_p:
** - Prints a pointer address as a hexadecimal.
*/

void	length_modifier_p(t_printf *flags)
{
	uintmax_t	ptr;

	ptr = va_arg(flags->args, unsigned long);
	print_hexadecimal(flags, ptr);
}
