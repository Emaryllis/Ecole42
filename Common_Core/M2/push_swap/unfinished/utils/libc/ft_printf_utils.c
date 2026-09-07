/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 00:05:26 by egoh              #+#    #+#             */
/*   Updated: 2025/09/10 00:05:26 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

int	ft_puthex(unsigned long n, int upper)
{
	char	*base;
	int		len;

	if (upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	len = 0;
	if (n >= 16)
		len += ft_puthex(n / 16, upper);
	len += write(1, &base[n % 16], 1);
	return (len);
}

int	ft_putstr(char *s)
{
	int	len;

	if (!s)
		return (ft_putstr("(null)"));
	len = 0;
	while (*s)
		len += write(1, s++, 1);
	return (len);
}

int	ft_putnbr(int nb)
{
	int	len;

	len = 0;
	if (nb == -2147483648)
		return (write(1, "-2147483648", 11));
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
		len += 1;
	}
	if (nb > 9)
		len += ft_putnbr(nb / 10);
	len += write(1, &(char){nb % 10 + '0'}, 1);
	return (len);
}

int	ft_putunbr(unsigned int n)
{
	int	len;

	len = 0;
	if (n >= 10)
		len += ft_putunbr(n / 10);
	len += write(1, &(char){n % 10 + '0'}, 1);
	return (len);
}
