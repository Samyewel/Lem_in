/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 18:54:19 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 21:39:48 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_strcmp:
** - Lexicographically compare the null-terminated strings s1 and s2.
*/

int	ft_strcmp(const char *s1, const char *s2)
{
	int				count;
	unsigned char	cmp1;
	unsigned char	cmp2;

	count = 0;
	while (s1[count] == s2[count] && s1[count] != '\0' && s2[count] != '\0')
		count++;
	cmp1 = (unsigned char) s1[count];
	cmp2 = (unsigned char) s2[count];
	return (cmp1 - cmp2);
}
