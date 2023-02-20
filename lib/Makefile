CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -I lib/include/ -I lib/ -I src/
LDFLAGS	:= -L "/Users/amorvai/.brew/opt/glfw/lib/" -L ./lib/MLX42/ -L lib -lmlx42 -ldl -lglfw -lm -g
VPATH	:= src/ src/calculate/ src/draw/ src/hooks/ src/init-free/ src/parsing/ lib/get_next_line/
OBJ_DIR	:= obj/
# HEADS	:=
NAME	:= fdf

SRC		:=	main.c \
			matrix_calculations.c \
			draw.c \
			draw_line.c \
			print_functions.c \
			rgba.c \
			hooks.c \
			change_matrices.c \
			init_matrices.c \
			init.c \
			free.c \
			parsing.c \
			parsing_utils.c \
			get_next_line_fd.c \
			get_next_line_utils_fd.c

OBJ		:=	$(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC)))

PRINTF	:= lib/printf/libftprintf.a

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(PRINTF)
	$(CC) $(OBJ) -o $(NAME) $(PRINTF) $(LDFLAGS)

$(OBJ_DIR)%.o: %.c 
	$(CC) $(CFLAGS) $< -c -o $@

$(OBJ_DIR): 
	mkdir obj

$(PRINTF):
	make --directory=./lib/printf

clean:
	make clean --directory=./lib/printf	
	rm -f $(OBJ)

fclean: clean
	make fclean --directory=./lib/printf
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
 # gnu make 10.7 old fashioned suffix rules