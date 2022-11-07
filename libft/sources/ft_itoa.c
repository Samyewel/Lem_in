/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:12:47 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 19:19:42 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** array_len:
** - Calculates the length of the array.
*/

static int	array_len(int n)
{
	int	i;

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

static char	*array(char *ascii, long result, size_t len)
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

char	*ft_itoa(int n)
{
	char				*ascii;
	long				result;
	size_t				len;

	len = array_len(n);
	ascii = ft_strnew(len + (n < 0));
	result = n;
	if (!(ascii))
		return (NULL);
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
