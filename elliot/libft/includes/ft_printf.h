/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:50:00 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/16 15:40:35 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# include "libft.h"
# include <fcntl.h>
# include <stdarg.h>
# include <unistd.h>

/*
** Struct for input data:
** - format:
**		- When reading which format specifier is used ('c', 'd', etc...), we
**		  save the character to a char to confirm its existence and for later
**		  use when refining which length modifier to use.
** - precision_specified:
**		- Used within precision conversion to account for cases where '0' is
**		  given as precision.
** - parsing_length:
**		- Used seperately from total_length to ensure accuracy when parsing
**		  through the input data.
** - total_length:
**		- Used to count the total bytes printed.
** - zero_padding:
**		- For all conversions except n, the converted value is padded
**		  on the left with zeros rather than blanks.  If a precision is given
**		  with a numeric conversion (d, i, o, u, i, x, and X), the 0 flag is
**		  ignored.
** - apostrophe:
**		- Decimal conversions (d, u, or i) or the integral portion of a
**		  floating point conversion (f or F) should be grouped and separated
**		  by thousands using the non-monetary separator returned by
**		  localeconv(3).
** - large_ell:
**		-
** - is_zero:
**		-
** - percent:
**		- A `%' is written.  No argument is converted.  The complete
**		  conversion specification is `%%'.
** - dollar:
**		-
** - period:
**		- Used to begin signal precision using the numbers after it.
** - width:
**		-
** - space:
**		- A blank should be left before a positive number produced by a
**		  signed conversion (a, A, d, e, E, f, F, g, G, or i).
** - dash:
**		- A negative field width flag; the converted value is to be left
**		  adjusted on the field boundary.  Except for n conversions, the
**		  converted value is padded on the right with blanks, rather than
**		  on the left with blanks or zeros.  A - overrides a 0 if both are
**		  given.
** - hash:
**		- The value should be converted to an ``alternate form''.
**		  For c, d, i, n, p, s, and u conversions, this option has no effect.
**		- For o conversions, the precision of the number is increased to
**		  force the first character of the output string to a zero.
**		- For x and X conversions, a non-zero result has the string `0x'
**		  (or `0X' for X conversions) prepended to it.
**		- For a, A, e, E, f, F, g, and G conversions, the result will always
**		  contain a decimal point, even if no digits follow it (normally, a
**		  decimal point appears in the results of those conversions only if a
**		  digit follows).
**		- For g and G conversions, trailing zeros are not removed from the
**		  result as they would otherwise be.
** - sign:
**		- A sign must always be placed before a number produced by a signed
**		  conversion. A + overrides a space if both are used.
** - star:
**		- Used when providing precision as an argument.
** - ell:
**		-
** - h:
**		-
** - j:
**		-
** - z:
**		-
**
*/
typedef struct s_printf
{
	va_list	args;
	char	format;
	int		fd;
	int		precision_specified;
	int		parsing_length;
	int		total_length;
	int		zero_padding;
	int		apostrophe;
	int		large_ell;
	int		precision;
	int		is_zero;
	int		percent;
	int		dollar;
	int		period;
	int		width;
	int		space;
	int		dash;
	int		hash;
	int		plus;
	int		sign;
	int		star;
	int		ell;
	int		h;
	int		j;
	int		z;
}	t_printf;

/*
** Main functions
*/
int			ft_dprintf(int fd, const char *input, ...);
int			ft_printf(const char *input, ...);

/*
** Flag handling
*/
int			update_flags(t_printf *flags, const char *input, int i);
t_printf	*initialise_flags(t_printf *flags);
t_printf	*initialise_reading_values(t_printf *flags, int fd);

/*
** Length modifiers
*/
void		length_modifier_c(t_printf *flags);
void		length_modifier_di(t_printf *flags);
void		length_modifier_f(t_printf *flags);
void		length_modifier_o(t_printf *flags);
void		length_modifier_p(t_printf *flags);
void		length_modifier_s(t_printf *flags);
void		length_modifier_u(t_printf *flags);
void		length_modifier_x(t_printf *flags);

/*
** Format functions
*/
void		print_char(t_printf *flags, char c);
void		print_decimal(t_printf *flags, uintmax_t u);
void		print_float_f(t_printf *flags, long double f);
void		print_hexadecimal(t_printf *flags, unsigned long long x);
void		print_integer(t_printf *flags, intmax_t d);
void		print_octal(t_printf *flags, uintmax_t o);
void		print_string(t_printf *flags, char *str);

/*
** Utilities
*/
char		*ft_printf_dtostr(double n, intmax_t power);
char		*ft_printf_signed_itoa(long long n);
char		*ft_printf_utoa_base(t_printf *flags, unsigned long long input,
				int base);
int			ft_printf_unsigned_number_length(unsigned long long n, int base);
long double	float_f_rounding(t_printf *flags, long double f);
char		*float_f_dtostr(t_printf *flags, long double f);

/*
** Error handling
*/
void		ft_printf_error(t_printf *flags, char *error_message);
void		ft_printf_strerror(char *error_message);

#endif
