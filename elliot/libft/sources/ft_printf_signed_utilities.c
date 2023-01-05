/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_signed_utilities.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:12:58 by swilliam          #+#    #+#             */
/*   Updated: 2022/09/13 12:32:58 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** array_len:
** - Calculates the length of the array.
*/

static int	array_len(long long n)
{
	int	i;

	if (n == 0)
		return (1);
	if (n < -9223372036854775807)
		return (20);
	i = !n;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

/*
** array:
** - The given character array is filled with converted ascii characters.
*/

static char	*array(char *ascii, long long result, size_t len)
{
	while (result > 0)
	{
		ascii[--len] = 48 + (result % 10);
		result = result / 10;
	}
	return (ascii);
}

/*
** ft_itoa:
** - Allocates (with malloc(3)) and returns a “fresh” string ending with ’\0’
**   representing the integer n given as argument.
**   Negative numbers must be supported.
** - If the allocation fails, the function returns NULL.
*/

char	*ft_printf_signed_itoa(long long n)
{
	char				*ascii;
	long				result;
	size_t				len;

	if (n < -9223372036854775807)
		return ("9223372036854775808");
	len = array_len(n);
	ascii = ft_strnew(len + (n < 0));
	if (!(ascii))
		return (NULL);
	result = n;
	if (n == 0)
	{
		ascii[0] = '0';
		return (ascii);
	}
	if (n < 0)
	{
		len++;
		ascii[0] = '-';
		result *= -1;
	}
	array(ascii, result, len);
	return (ascii);
}
