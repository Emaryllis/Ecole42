/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#define HEX_DIGITS "0123456789abcdef"

void	print_hex(unsigned char c)
{
	char	hex_output[2];

	hex_output[0] = HEX_DIGITS[c / 16];
	hex_output[1] = HEX_DIGITS[c % 16];
	write(1, hex_output, 2);
}

void	print_memory_address(void *addr)
{
	unsigned long int	addr_int;
	char				addr_hex[17];
	int					i;

	addr_int = (unsigned long int)addr;
	i = 15;
	while (i >= 0)
	{
		addr_hex[i] = HEX_DIGITS[addr_int % 16];
		addr_int /= 16;
		i--;
	}
	addr_hex[16] = '\0';
	write(1, addr_hex, 16);
}

void	print_hex_content(unsigned char *ptr, unsigned int i, unsigned int size)
{
	unsigned int	line_i;

	line_i = 0;
	while (line_i < 16 && i + line_i < size)
	{
		if (line_i % 2 == 0 && line_i != 0)
			write(1, " ", 1);
		print_hex(ptr[i + line_i]);
		line_i++;
	}
	while (line_i < 16)
	{
		if (line_i % 2 == 0 && line_i != 0)
			write(1, " ", 1);
		write(1, "  ", 2);
		line_i++;
	}
}

void	print_printable_chars(
		unsigned char *ptr, unsigned int i, unsigned int size)
{
	unsigned int	line_i;

	line_i = 0;
	while (line_i < 16 && i + line_i < size)
	{
		if (ptr[i + line_i] >= 32 && ptr[i + line_i] <= 126)
			write(1, &ptr[i + line_i], 1);
		else
			write(1, ".", 1);
		line_i++;
	}
}

void	ft_print_memory(void *addr, unsigned int size)
{
	unsigned char	*ptr;
	unsigned int	i;

	ptr = (unsigned char *)addr;
	i = 0;
	if (size == 0)
		return ;
	while (i < size)
	{
		print_memory_address(&ptr[i]);
		write(1, ": ", 2);
		print_hex_content(ptr, i, size);
		write(1, " ", 1);
		print_printable_chars(ptr, i, size);
		write(1, "\n", 1);
		i += 16;
	}
}
