/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}

//#include <stdio.h>
//int main (void)
//{
//	char str[][5] = { "R2D2" , "C3PO" , "R2A6" };
//	int n;
//	for (n=0 ; n<3 ; n++)
//		if (ft_strncmp(str[n],"R2xx",2) == 0)
//		{
//			printf ("found %s\n",str[n]);
//		}
//	return 0;
//}