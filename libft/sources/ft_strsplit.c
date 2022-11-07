/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:13:19 by swilliam          #+#    #+#             */
/*   Updated: 2022/10/20 16:30:44 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strsplit:
** - Allocates (with malloc(3)) and returns an array of “fresh” strings
**   (all ending with ’\0’, including the array itself), obtained by
**   splitting s using the character c as a delimiter.
** - If the allocation fails the function returns NULL.
*/

static size_t	wordlen(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			s++;
			count++;
		}
		else
			return (count);
	}
	return (count);
}

static char	**create_array(char	**array, char const *s, char c
, size_t wordcount)
{
	size_t	x;
	size_t	i;
	size_t	len;

	x = 0;
	i = -1;
	while (++i < wordcount && array)
	{
		while (s[x] == c && s[x])
			x++;
		len = wordlen(&s[x], c);
		array[i] = ft_strnew(len);
		if (!(array[i]))
		{
			ft_arrdel(array);
			return (NULL);
		}
		ft_strncpy(array[i], &s[x], len);
		array[i][len] = '\0';
		while (s[x] != c && s[x])
			x++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**array;

	array = (char **)ft_memalloc(sizeof (char *) * (ft_wordcount(s, c) + 1));
	if (!(array))
		return (NULL);
	array = create_array(array, s, c, ft_wordcount(s, c));
	if (!(array))
		return (NULL);
	return (array);
}
