#include <stdio.h>

int ft_scanf(const char *, ...);

// cc ft_scanf.c main.c -o ft_scanf
int main(void) {
	char x[100];
	char str[100];
	char c;

	int converted = ft_scanf("%s %s %c", &x, str, &c);

	printf("Converted: %d\n", converted);
	printf("Number: %s, String: %s, Character: %c\n", x, str, c);

	return 0;
}
