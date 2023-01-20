/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:56:18 by sam               #+#    #+#             */
/*   Updated: 2023/01/19 18:59:33 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int value, int base)
{
	int	len;

	len = 0;
	if (value == 0)
		return (1);
	while (value > 0)
	{
		value /= base;
		len++;
	}
	return (len);
}

char	*ft_itoa_base(int value, int base)
{
	char	*radix;
	char	*res;
	int		len;
	int		sign;

	radix = "0123456789ABCDEF";
	sign = 0 + (value < 0 && base == 10);
	if (value < 0)
		value *= -1;
	len = ft_numlen(value, base) + sign;
	res = (char *)malloc(sizeof(char) * len + 1);
	if (!res)
		return (0);
	res[len + 1] = '\0';
	while (len-- > sign)
	{
		res[len] = radix[value % base];
		value /= base;
	}
	if (len == 0 && sign)
		res[len] = '-';
	return (res);
}
