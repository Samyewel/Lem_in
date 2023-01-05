/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:31:48 by sam               #+#    #+#             */
/*   Updated: 2022/10/03 15:48:09 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1
# define FD_SIZE 4096
/*
** Inclusions
*/
# include "libft.h"
# include <unistd.h>
/*
** Prototypes
*/
int	get_next_line(const int fd, char **line);

#endif