/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:06:19 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 19:21:20 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_striteri:
** - Applies the function f to each character of the string passed
**   as argument, and passing its index as first argument.
** - Each character is passed by address to f to be modified if necessary.
*/

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	x;

	x = 0;
	if (!s || !f)
		return ;
	while (s[x])
	{
		f(x, s + x);
		x++;
	}
}
