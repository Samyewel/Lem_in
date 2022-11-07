/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:33:16 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 20:01:46 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_toupper:
** - Converts a lowercase alphabetical character into an uppercase
**   character.
*/

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c = c - 32;
	return (c);
}
