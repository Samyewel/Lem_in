# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sam <sam@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 13:26:33 by swilliam          #+#    #+#              #
#    Updated: 2022/12/05 16:38:32 by sam              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Source files
LEM_IN_DIR = ./sources/
LEM_IN_FILES = main.c read_input.c list_utils.c print_data.c \
list_creation.c path_flow.c queue.c clean_data.c

# Libft
LIBFT_DIR = ./libft/
LIBFT = libft.a

# Object files
OBJ_DIR = ./objects/
OBJ = $(addprefix $(OBJ_DIR), $(LEM_IN_FILES:.c=.o))

# Compilation
CC = gcc
FLAGS = -Wall -Wextra -Werror
DEBUG = -g
INCLUDES = -I./includes -I$(LIBFT_DIR)includes -I./eval_tests
ADD_LIB = -L. $(LIBFT)
LEM_IN = lem-in

# Utilities
DELETE = $(LEM_IN) $(OBJ)
#PLAYER = ./eval_tests/play.py
TEST_CMD = ./lem-in < ./resources/maps/

all:		$(LEM_IN)

$(LEM_IN): $(OBJ) $(OBJ_DIR)
			@make all -C $(LIBFT_DIR)
			@printf "\r                                       \r"
			@$(CC) $(FLAGS) $(INCLUDES) $(OBJ) $(LIBFT_DIR)$(LIBFT) -o $(LEM_IN)
			@printf "\r                                       \r"
			@printf "\rExecutable ($(LEM_IN)) created.\n"

$(OBJ_DIR)%.o: $(LEM_IN_DIR)%.c
			@mkdir -p $(OBJ_DIR)
			@printf "\rCompiling objects..."
			@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
			@printf "\r                                       \r"

clean:
			@printf "\rCleaning objects..."
			@make clean -sC $(LIBFT_DIR)
			@rm -f $(OBJ)
			@rm -rf $(OBJ_DIR)
			@printf "\r                                       \r"
			@printf "\rObjects cleaned.\n"

fclean: 	clean
			@printf "\rCleaning all created files..."
			@make fclean -sC $(LIBFT_DIR)
			@rm -f $(DELETE)
			@printf "\r                                       \r"
			@printf "\rAll created files removed.\n"

re:			fclean all

test0:		all
			@$(TEST_CMD)0.map

test1:		all
			@$(TEST_CMD)1.map

test2:		all
			@$(TEST_CMD)2.map

.PHONY: all clean fclean re