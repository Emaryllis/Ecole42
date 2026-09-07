NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = check_unique.c ft_split.c init_data.c intlist.c main.c ops.c push_swap.c\
small_sort.c utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
