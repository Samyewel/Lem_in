/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:36:10 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 19:21:11 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strdup:
** - Allocates sufficient memory for a copy of the string s1, does the
**   copy, and returns a pointer to it.
*/

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		i;
	int		len;

	len = ft_strlen(s1);
	dup = ft_strnew(len);
	if (!(dup))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	return (dup);
}
