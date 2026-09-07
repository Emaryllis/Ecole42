# Variables
NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
SRC = ft_printf.c utils/ft_putchar.c utils/ft_puthex.c utils/ft_putnbr.c \
	utils/ft_putstr.c utils/ft_putunbr.c
OBJ = $(SRC:.c=.o)

# Patterns
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re