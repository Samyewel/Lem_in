/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:43:41 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 19:21:41 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strncmp:
** - Lexicographically compare the null-terminated strings s1 and s2 up to
**   no more than n characters.
** - characters that appear after a `\0' character are not compared.
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			count;
	unsigned char	cmp1;
	unsigned char	cmp2;

	count = 0;
	if (n == 0)
		return (0);
	while (count < n - 1 && s1[count] == s2[count] && (s1[count] != '\0'
			&& s2[count] != '\0'))
		count++;
	cmp1 = (unsigned char) s1[count];
	cmp2 = (unsigned char) s2[count];
	return (cmp1 - cmp2);
}
