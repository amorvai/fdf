# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/04 14:52:03 by amorvai           #+#    #+#              #
#    Updated: 2022/05/05 14:36:58 by amorvai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= cc
CFLAGS	:= -Wall  -Wextra -Werror
NAME	:= libftprintf.a
SRC		:=	ft_printf.c \
			print_conversions/print_char.c \
			print_conversions/print_int.c \
			print_conversions/print_lowerhexadec.c \
			print_conversions/print_string.c \
			print_conversions/print_unsigneddecimal.c \
			print_conversions/print_upperhexadec.c \
			print_conversions/print_voidptr.c

OBJ 	:= $(SRC:.c=.o)
LIBFT	:= libft/libft.a

all: $(LIBFT) $(NAME) 

$(LIBFT):
	make --directory=./libft

$(NAME): $(OBJ) $(LIBFT)
	cp libft/libft.a $(NAME)
	ar -crs $(NAME) $(OBJ) 

clean:
	make clean --directory=./libft
	rm -f $(OBJ)

fclean: clean
	make fclean --directory=./libft
	rm -f $(NAME) 

re: fclean all 

.PHONY: all clean fclean re