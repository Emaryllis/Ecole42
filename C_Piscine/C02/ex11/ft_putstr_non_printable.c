/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	print_hex(int np)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (np > 16)
	{
		print_hex(np / 10);
		print_hex(np % 10);
	}
	else
		write(1, &hex[np], 1);
}

void	ft_putstr_non_printable(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((str[i] <= 31 && str[i] >= 0) || str[i] == 127)
		{
			write(1, "\\", 1);
			if (str[i] < 16)
				write(1, "0", 1);
			print_hex(str[i]);
		}
		else
			write(1, &str[i], 1);
		i += 1;
	}
	write(1, "\n", 1);
}

//#include <stdio.h>
//int main(void) {
//	// Test 1: String with non-printable characters
//	ft_putstr_non_printable("Hello\nWorld!"); // Expected output: Hello\0aWorld!
//	printf("\n");
//
//	// Test 2: String with no non-printable characters
//	ft_putstr_non_printable("Hello World!"); // Expected output: Hello World!
//	printf("\n");
//
//	// Test 3: Empty string
//	ft_putstr_non_printable(""); // Expected output: (empty string)
//	printf("\n");
//
//	// Test 4: String with all non-printable characters
//	// Expected output: \07\08\0c\0a\0d\09\0b
//	ft_putstr_non_printable("\a\b\f\n\r\t\v");
//	return 0;
//}