NAME = ft_display_file
FLAGS = -Wall -Werror -Wextra
SRC = main.c
OBJS = $(patsubst %.c, %.o, $(SRC))

all: $(NAME)

$(NAME):
	cc $(FLAGS) -c $(SRC)
	cc $(FLAGS) -o $(NAME) $(OBJS)

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all