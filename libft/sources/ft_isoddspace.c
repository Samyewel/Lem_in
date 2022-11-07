/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isoddspace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:29:54 by sam               #+#    #+#             */
/*   Updated: 2021/12/12 17:17:25 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_isoddspace:
** - Checks for characters that will be skipped within the string, 
**	 before the ascii characters.
*/

int	ft_isoddspace(int c)
{
	return (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r');
}
