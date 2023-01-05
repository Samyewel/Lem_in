/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:33:23 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 20:00:30 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_tolower:
** - Converts an uppercase alphabetical character into an lowercase
**   character.
*/

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c = c + 32;
	return (c);
}
