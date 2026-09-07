# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egoh <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/29 14:07:53 by egoh              #+#    #+#              #
#    Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror
MINILIBX = minilibx-linux
SRC = init.c listeners.c main.c render.c util_math.c util_str.c
OBJ = $(SRC:.c=.o)

# Rules
all: $(NAME)

# mlx_Linux requires X11 (-lX11) and Xext (-lXext) libraries
$(NAME): $(OBJ)
	make -C $(MINILIBX)
	$(CC) $(CFLAGS) -o $@ $^ -Lminilibx-linux -lmlx_Linux -lX11 -lXext

clean:
	rm -f $(OBJ)
	make -C $(MINILIBX) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re