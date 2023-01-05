/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:13:14 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 19:21:36 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strmapi:
** - Applies the function f to each character of the string passed as argument
**   by giving its index as first argument to create a “fresh” new
**   string (with malloc(3)) resulting from the successive applications of f.
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t		x;
	size_t		len;
	char		*newstr;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	newstr = ft_strnew(len);
	if (!(newstr))
		return (NULL);
	x = 0;
	while (s[x])
	{
		newstr[x] = f(x, s[x]);
		x++;
	}
	return (newstr);
}
