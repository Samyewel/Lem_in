/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:33:04 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 19:22:02 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrev(char *str)
{
	char	rev[100];
	int		i;
	int		length;

	i = 0;
	length = ft_strlen(str);
	while (i < length)
	{
		rev[i] = str[i];
		str[i] = str[length - i - 1];
		str[length - i - 1] = rev[i];
		i++;
	}
	str[i] = '\0';
}
