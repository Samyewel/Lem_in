/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:30:16 by sam               #+#    #+#             */
/*   Updated: 2023/02/19 15:33:54 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** clean_lem_in:
** - Upon finding an error, all necessary data is cleaned before exiting the
**   program.
*/

void	clean_lem_in(char *str)
{
	ft_dprintf(1, str);
	exit(EXIT_FAILURE);
}
