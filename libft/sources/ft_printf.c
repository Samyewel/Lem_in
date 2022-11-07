/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:46:11 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/04 15:04:21 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** handle_conversion:
** - When a specific conversion format is met, we pass it to a length modifier
**   function to process which flags have been given to convert it to it's
**   correct length.
*/

static void	handle_conversion(t_printf *flags)
{
	if (flags->format == 'd' || flags->format == 'D' || flags->format == 'i')
		length_modifier_di(flags);
	if (flags->format == 'o' || flags->format == 'O')
		length_modifier_o(flags);
	if (flags->format == 'u' || flags->format == 'U')
		length_modifier_u(flags);
	if (flags->format == 'x' || flags->format == 'X')
		length_modifier_x(flags);
	if (flags->format == 'c' || flags->format == 'C')
		length_modifier_c(flags);
	if (flags->format == 's' || flags->format == 'S')
		length_modifier_s(flags);
	if (flags->format == 'p')
		length_modifier_p(flags);
	if (flags->format == '%')
		print_char(flags, '%');
	if (flags->format == 'f' || flags->format == 'F')
		length_modifier_f(flags);
	if (flags->format == 'Z')
		flags->total_length += write(1, "Z", 1);
}

/*
** evaluate_format:
** - We read through the given input string, updating the flags to our struct
**   as they are found. Once a format specification is found, we set it as our
**   format in our struct for future accuracy during conversion.
** - once the conversion has been completed, our flags are initialised once
**   again for when another argument is given to be converted.
*/

int	evaluate_format(t_printf *flags, const char *input, int i)
{
	while ((input[i] != 'd' && input[i] != 'D') && input[i] != 'i'
		&& (input[i] != 'o' && input[i] != 'O')
		&& (input[i] != 'u' && input[i] != 'U')
		&& (input[i] != 'x' && input[i] != 'X')
		&& (input[i] != 'c' && input[i] != 'C')
		&& (input[i] != 's' && input[i] != 'S')
		&& input[i] != 'p' && input[i] != '%'
		&& input[i] != 'f' && input[i] != 'F'
		&& input[i] != 'Z')
	{
		if (update_flags(flags, input, i) != 1)
			ft_printf_error(flags, "Too many repeated flags found. "
				"Invalid input.");
		if (input[i] == '\0' || input[i + 1] == '\0')
			ft_printf_error(flags, "Conversion format character not found.");
		i++;
	}
	flags->format = input[i];
	handle_conversion(flags);
	initialise_flags(flags);
	return (i);
}

/*
** ft_dprintf:
** - Acts the same as ft_printf, except a file descriptor is given.
*/

int	ft_dprintf(int fd, const char *input, ...)
{
	int			i;
	int			length;
	t_printf	*flags;

	i = -1;
	length = 0;
	flags = (t_printf *)malloc(sizeof(t_printf));
	if (!flags)
		ft_printf_error(flags, "Failed to allocate memory for flags.");
	initialise_reading_values(flags, fd);
	initialise_flags(flags);
	va_start(flags->args, input);
	while (input[++i])
	{
		if (input[i] == '%')
			i = evaluate_format(flags, input, i + 1);
		else
			flags->parsing_length += write(flags->fd, &input[i], 1);
	}
	va_end(flags->args);
	length += (flags->parsing_length + flags->total_length);
	free(flags);
	return (length);
}

/*
** ft_printf:
** - Initialises all flags in preparation for reading the input data, setting
**   the file descriptor to 1 as this form of printf does not specify a
**   custom file descriptor.
** - Parses through to the end of the string, pausing to evaluate the
**   conversion request when a % is found.
*/

int	ft_printf(const char *input, ...)
{
	int			i;
	int			length;
	t_printf	*flags;

	i = -1;
	length = 0;
	flags = (t_printf *)malloc(sizeof(t_printf));
	if (!flags)
		ft_printf_error(flags, "Failed to allocate memory for flags.");
	initialise_reading_values(flags, 1);
	initialise_flags(flags);
	va_start(flags->args, input);
	while (input[++i])
	{
		if (input[i] == '%')
			i = evaluate_format(flags, input, i + 1);
		else
			flags->parsing_length += write(flags->fd, &input[i], 1);
	}
	va_end(flags->args);
	length += (flags->parsing_length + flags->total_length);
	free(flags);
	return (length);
}
