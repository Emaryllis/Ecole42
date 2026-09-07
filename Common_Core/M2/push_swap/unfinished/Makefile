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
NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_ROOT = main.c a_star_chunk_sort.c
SRC_LIBC = ft_printf.c ft_printf_utils.c ft_putstr_fd.c ft_split.c ft_sqrt.c \
ft_strcmp.c
SRC_UTIL = init_data.c ops.c ops_both.c small_sort.c util_int.c util_stack.c \
debug.c

SRC = $(SRC_ROOT) $(addprefix utils/libc/, $(SRC_LIBC)) \
      $(addprefix utils/, $(SRC_UTIL))
OBJ_DIR = build
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/utils/libc $(OBJ_DIR)/utils

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
