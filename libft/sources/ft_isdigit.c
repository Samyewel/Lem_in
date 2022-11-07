/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:07:15 by swilliam          #+#    #+#             */
/*   Updated: 2021/12/12 17:17:13 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_isdigit:
** - Checks if the input integer is an numeric ascii character.
*/

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
