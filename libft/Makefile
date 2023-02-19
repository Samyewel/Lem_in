# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sam <sam@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 13:26:33 by swilliam          #+#    #+#              #
#    Updated: 2023/02/19 16:48:54 by sam              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_strcmp.c ft_strncmp.c ft_strdup.c ft_strlen.c ft_toupper.c \
ft_tolower.c ft_strstr.c ft_strnstr.c ft_strchr.c ft_strrchr.c ft_strcpy.c \
ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_isdigit.c ft_isascii.c \
ft_isalpha.c ft_isalnum.c ft_isprint.c ft_atoi.c ft_putchar.c ft_putstr.c \
ft_putnbr.c ft_putendl.c ft_strequ.c ft_strnequ.c ft_memset.c ft_bzero.c \
ft_memchr.c ft_memcpy.c ft_memccpy.c ft_memcmp.c ft_memmove.c ft_striter.c \
ft_striteri.c ft_memalloc.c ft_strnew.c ft_strclr.c ft_memdel.c ft_strdel.c \
ft_strmap.c ft_strmapi.c ft_itoa.c ft_strjoin.c ft_putchar_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_putstr_fd.c ft_strtrim.c ft_strsub.c ft_strsplit.c ft_lstadd.c \
ft_lstnew.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_isnumber.c \
ft_isoddspace.c ft_iswhitespace.c ft_arrdel.c ft_wordcount.c ft_max.c ft_min.c \
ft_itoa_base.c ft_sort_int_tab.c ft_make_grid.c ft_charcount.c \
get_next_line.c \
ft_printf.c \
print_char.c print_integer.c print_string.c print_octal.c \
print_decimal.c print_hexadecimal.c print_float_f.c \
length_modifier_c.c \
length_modifier_di.c \
length_modifier_f.c \
length_modifier_o.c \
length_modifier_u.c \
length_modifier_x.c \
length_modifier_s.c \
length_modifier_p.c \
ft_printf_error.c ft_printf_flags.c \
ft_printf_unsigned_utilities.c \
ft_printf_signed_utilities.c ft_printf_float_f_utilities.c

SRC_DIR = ./sources/
OBJ_DIR = ./objects/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I includes

all: 		$(NAME)

$(NAME): 	$(OBJ)
			@printf "\rCompiling libft..."
			@ar rc $(NAME) $(OBJ)
			@ranlib $(NAME)
			@printf "\r                                       \r"
			@printf "\rLibft compiled."

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			@mkdir -p $(OBJ_DIR)
			@$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
			@rm -f $(OBJ)
			@rm -rf $(OBJ_DIR)

fclean: 	clean
			@rm -f $(NAME)

re:			fclean all

.PHONY: all debug clean fclean re