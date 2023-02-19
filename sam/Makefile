# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sam <sam@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 13:26:33 by swilliam          #+#    #+#              #
#    Updated: 2023/02/19 13:34:54 by sam              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Source files
LEM_IN_DIR = ./sources/
LEM_IN_FILES = \
main.c read_input.c \
room_creation.c room_utils.c link_creation.c \
path_creation.c path_utils.c \
backtrack_paths.c \
solution_creation.c usage_calculation.c best_solution.c \
printer.c printing_utils.c \
ant_creation.c \
debug_printing.c clean_data.c \
error_check.c error_check2.c \
utils.c flow_calculation.c queue.c bfs_graph.c

# Libft
LIBFT_DIR = ../libft/
LIBFT = libft.a

# Object files
OBJ_DIR = ./objects/
OBJ = $(addprefix $(OBJ_DIR), $(LEM_IN_FILES:.c=.o))

# Compilation
CC = gcc
FLAGS = -Wall -Wextra -Werror
FS = -fsanitize=address
DEBUG = -g
INCLUDES = -I./includes -I$(LIBFT_DIR)includes -I./eval_tests
ADD_LIB = -L. $(LIBFT)
LEM_IN = lem-in

# Utilities
DELETE = $(LEM_IN) $(OBJ)
EVAL = ../eval_tests/
OUT = ../eval_tests/output/
TEST_CMD = ./lem-in < $(EVAL)maps/
GENERATOR = $(EVAL)generator

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
			@rm -rf $(OUT)
			@printf "\r                                       \r"
			@printf "\rObjects cleaned.\n"

fclean: 	clean
			@printf "\rCleaning all created files..."
			@make fclean -sC $(LIBFT_DIR)
			@rm -f $(DELETE)
			@printf "\r                                       \r"
			@printf "\rAll created files removed.\n"

re:			fclean all

f1:			all
			@mkdir -p $(OUT)
			@$(GENERATOR) --flow-one > $(OUT)flow1.map
			@time ./lem-in < $(OUT)flow1.map

f10:		all
			@mkdir -p $(OUT)
			@$(GENERATOR) --flow-ten > $(OUT)flow10.map
			@time ./lem-in < $(OUT)flow10.map

f1000:		all
			@mkdir -p $(OUT)
			@$(GENERATOR) --flow-thousand > $(OUT)flow1000.map
			@time ./lem-in < $(OUT)flow1000.map

big:		all
			@mkdir -p $(OUT)
			@$(GENERATOR) --big > $(OUT)big.map
			@time ./lem-in < $(OUT)big.map

super:		all
			@mkdir -p $(OUT)
			@$(GENERATOR) --big-superposition > $(OUT)big-superposition.map
			@time ./lem-in < $(OUT)big-superposition.map

test0:		all
			@time $(TEST_CMD)0.map

test1:		all
			@time $(TEST_CMD)1.map

test2:		all
			@time $(TEST_CMD)2.map

test3:		all
			@time $(TEST_CMD)3.map

test4:		all
			@time $(TEST_CMD)4.map

test5:		all
			@time $(TEST_CMD)5.map

.PHONY: all clean fclean re