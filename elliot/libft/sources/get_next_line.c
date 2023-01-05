/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:53:51 by sam               #+#    #+#             */
/*   Updated: 2022/08/25 19:22:23 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**	gnl_handle_line:
**  - If a newline character is found, the function will duplicate the
**	  content of the file to a temporary string, then will duplicate once
**    again to the output line string up until just before the newline
**    character.
**  - When a newline is found and the text has been copied, array[fd] is
**    updated to contain everything after the newline for the next read
**    attempt.
**	- If a newline character is not found, it will only otherwise be a
**	  end-of-file, therefore duplicating everything up to that point. It
**    then sets array[fd] to NULL so that on the next read attempt, it
**    will be seen as empty and therefore reading will end and return 0.
*/

static int	gnl_handle_line(const int fd, char **line, char **array)
{
	char	*temp;

	if (ft_strchr(array[fd], '\n') != NULL)
	{
		*line = ft_strsub(array[fd], 0, ft_strchr(array[fd], '\n') - array[fd]);
		temp = ft_strdup(ft_strchr(array[fd], '\n') + 1);
		if (temp == NULL)
		{
			ft_strdel(&temp);
			return (-1);
		}
		ft_strdel(&(array[fd]));
		array[fd] = ft_strdup(temp);
		ft_strdel(&temp);
		if (array[fd][0] == '\0')
			ft_strdel(&(array[fd]));
	}
	else
	{
		*line = ft_strdup(array[fd]);
		ft_strdel(&(array[fd]));
	}
	return (1);
}

/*
**	gnl_return_value:
**  - If an error is encountered in gnl_read_file, -1 is returned.
**  - If file ends during reading process, 0 is returned.
**  - If no error or end-of-file is encountered, line is modified within
**    gnl_handle_line to contain the next line of text within the file.
*/

static int	gnl_return_value(const int fd, char **line, char **array, int bytes)
{
	if (bytes < 0)
		return (-1);
	else if (bytes == 0 && array[fd] == NULL)
		return (0);
	else
		return (gnl_handle_line(fd, line, array));
}

/*
**	gnl_read_file:
**  - Reads bytes up until either a newline or end-of-file, storing
**    the text in the buffer (buf) string on the stack memory.
**	- If, before the next read attempt, a newline is already found,
**    the loop is broken to prevent wasted time with unnecessary
**    reading.
**  - If file is ends or encounters an error, the subsequent output
**    is returned in gnl_return_value.
**  - The buffer string is manually null-terminated.
**  - During the first read attempt, the entire buffer string is
**    duplicated onto the heap within array[fd] to make it accessible.
**  - Any read attempts after the first, the heap allocated string will
**    update itself to contain the next read line.
*/

static int	gnl_read_file(const int fd, char **line, char **array)
{
	int		bytes;
	char	buf[BUFF_SIZE + 1];
	char	*temp;

	bytes = 1;
	while (bytes > 0)
	{
		if (array[fd] != NULL && ft_strchr(array[fd], '\n') != NULL)
			break ;
		bytes = read(fd, buf, BUFF_SIZE);
		if (bytes <= 0)
			return (gnl_return_value(fd, line, array, bytes));
		buf[bytes] = '\0';
		if (array[fd] == NULL)
			array[fd] = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(array[fd], buf);
			ft_strdel(&(array[fd]));
			array[fd] = temp;
		}
		if (ft_strchr(array[fd], '\n') != NULL)
			break ;
	}
	return (gnl_return_value(fd, line, array, bytes));
}

/*
**	get_next_line:
**	- fd = the file descriptor that will be used to read.
** 	- line = the address of a pointer to a character that will be used
**	  to save the line read from the file descriptor.
**	- Initialises a static character array to update the contents
**	  read from the corresponding file descriptor.
**	- Returns -1 in gnl_return_value if any error-causing values
**	  are provided.
**	- If all error checks are completed, reading process begins.
*/

int	get_next_line(const int fd, char **line)
{
	static char	*array[FD_SIZE];

	if (!line || fd < 0 || fd > FD_SIZE || BUFF_SIZE < 1)
		return (gnl_return_value(fd, line, array, -1));
	return (gnl_read_file(fd, line, array));
}
