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
NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = pipex.c utils/ft_putstr_fd.c utils/ft_split.c utils/ft_strchr.c \
utils/ft_strdup.c utils/ft_strjoin.c utils/ft_strnstr.c utils/utils.c
OBJ = $(SRC:.c=.o)

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(OBJ_B)

fclean: clean
	rm -f $(NAME) $(NAME_B)

re: fclean all

.PHONY: all clean fclean re bonus