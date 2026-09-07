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
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = dinner.c init.c main.c monitor.c parse.c utils/display_utils.c \
utils/mutex_utils.c utils/sync_utils.c utils/thread_utils.c \
utils/time_utils.c utils/utils.c

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