LIB:=libft.a
SRC_DIR:=srcs
INCLUDE_DIR=includes

SRCS:=$(SRC_DIR)/ft_putchar.c $(SRC_DIR)/ft_putstr.c $(SRC_DIR)/ft_strcmp.c $(SRC_DIR)/ft_strlen.c $(SRC_DIR)/ft_swap.c

OBJS:=$(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRCS))

all: $(LIB)

$(OBJS): $(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	cc -Wall -Wextra -Werror -c $< -o $@ -I$(INCLUDE_DIR)

$(LIB_NAME): $(OBJS)
	ar rcs $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIB_NAME)

re: fclean all

.PHONY:	all clean fclean re
