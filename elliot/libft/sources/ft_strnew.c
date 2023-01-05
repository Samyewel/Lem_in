/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:13:17 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 19:21:52 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strnew:
** - Allocates (with malloc(3)) and returns a “fresh” string ending with ’\0’.
** - Each character of the string is initialized at ’\0’.
** - If the allocation fails, the function returns NULL.
*/

char	*ft_strnew(size_t size)
{
	char	*fresh;
	size_t	i;

	if (size < 0)
		return (NULL);
	fresh = (char *) malloc (sizeof(char) * size + 1);
	if (!(fresh))
		return (NULL);
	i = 0;
	while (i <= size)
	{
		fresh[i] = '\0';
		++i;
	}
	return (fresh);
}
