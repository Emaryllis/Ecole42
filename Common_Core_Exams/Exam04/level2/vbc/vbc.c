#include "vbc.h"

int ft_factor(char **s)
{
	int n = 0;

	if (isdigit((unsigned char)**s))
		return *(*s)++ - '0';
	if (**s == '(')
	{
		(*s)++;
		n = ft_sum(s);
		(*s)++;
	}
	return n;
}

int ft_product(char **s)
{
	int a = ft_factor(s);

	while (**s == '*' || isdigit((unsigned char)**s) || **s == '(')
	{
		if (**s == '*')
			(*s)++;
		a *= ft_factor(s);
	}
	return a;
}

int ft_sum(char **s)
{
	int sum1 = ft_product(s);

	while (**s == '+')
	{
		(*s)++;
		sum1 += ft_product(s);
	}
	return sum1;
}

int main(int argc, char **argv) {
	if (argc != 2)
		return 1;
	char *str = argv[1];
    if (check_input(str))
		return 1;
    int sum = ft_sum(&str);
	if (*str)
		return 1;
    printf("%d\n", sum);
}
