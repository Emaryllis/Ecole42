LIB_NAME="libft"
SRC_FILES="ft_putchar.c ft_putstr.c ft_strcmp.c ft_strlen.c ft_swap.c"

echo "Source files compiling..."
cc -Wall -Wextra -Werror -c "$SRC_FILES"

if [ $? -eq 0 ]; then
	echo "Source files compiled!"
else
	echo "Compiling failed!"
	exit 1
fi

echo "Beginning library creation..."
ar rcs $LIB_NAME.a *.o

if [ $? -eq 0 ]; then
	echo "$LIB_NAME library created!"
else
	echo "Library creation failed!"
	exit 1
fi
