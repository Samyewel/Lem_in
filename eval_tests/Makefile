# The ultimate Lem-in Makefile.
LEM_IN = lem-in
LEM_IN_DIR = ../
MAPS = ./maps/
OUT = ./output/
RUN = @time ../lem-in $(INPUT_FLAGS)
GENERATOR = ./generator
INPUT_FLAGS = -
# Input flags:
# a - Hides the printed ant moves.
# i - Hides the given input map.
# l - Prints lines used for ant movement turns.
# s - Prints the solution found.
# p - Prints the path nodes found via the BFS and when printing the solution
# g - Prints the residual graph during the BFS process.

all:
			@make all -C $(LEM_IN_DIR)

clean:
			@make clean -C $(LEM_IN_DIR)

fclean:		clean
			@make fclean -C $(LEM_IN_DIR)
			@rm -rf $(OUT)

re:			fclean all

norm:
			@norminette ../libft
			@norminette ../includes
			@norminette ../sources

error1:		all
			@mkdir -p $(OUT)
			@sh test_error.sh ./maps/error_1/$1

error2:		all
			@mkdir -p $(OUT)
			@sh test_error.sh ./maps/error_2/$1

error3:		all
			@mkdir -p $(OUT)
			@sh test_error.sh ./maps/error_3/$1

gauntlet:	all
			@sh mini_gauntlet.sh

gen:		all
			@sh make_thousand.sh

f1:			all
			@mkdir -p $(OUT)
			@$(GENERATOR) --flow-one > $(OUT)flow1.map
			$(RUN) < $(OUT)flow1.map

f10:		all
			@mkdir -p $(OUT)
			@$(GENERATOR) --flow-ten > $(OUT)flow10.map
			$(RUN) < $(OUT)flow10.map

f1000:		all
			@mkdir -p $(OUT)
			@$(GENERATOR) --flow-thousand > $(OUT)flow1000.map
			$(RUN) < $(OUT)flow1000.map

big:		all
			@mkdir -p $(OUT)
			@$(GENERATOR) --big > $(OUT)big.map
			$(RUN) < $(OUT)big.map

super:		all
			@mkdir -p $(OUT)
			@$(GENERATOR) --big-superposition > $(OUT)big-superposition.map
			$(RUN) < $(OUT)big-superposition.map

.PHONY: all clean fclean re norm error_1 error_2 error_3 gauntlet gen f1 f10 \
f1000 big super