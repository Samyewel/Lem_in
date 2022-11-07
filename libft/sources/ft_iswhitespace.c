/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:25:45 by sam               #+#    #+#             */
/*   Updated: 2022/08/25 19:19:38 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_iswhitespace:
** - Checks if the input integer is a whitespace character.
*/

int	ft_iswhitespace(size_t c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}
