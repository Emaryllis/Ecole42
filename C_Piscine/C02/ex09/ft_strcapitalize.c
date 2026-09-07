/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
int	if_alpha(char *str, int i, int new_word)
{
	if (new_word)
	{
		new_word = 0;
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] = str[i] - 32;
		}
	}
	else if (str[i] >= 'A' && str[i] <= 'Z')
	{
		str[i] = str[i] + 32;
	}
	return (new_word);
}

char	*ft_strcapitalize(char *str)
{
	int	i;
	int	new_word;

	i = 0;
	new_word = 1;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (
				str[i] >= 'A' && str[i] <= 'Z'))
		{
			new_word = if_alpha(str, i, new_word);
		}
		else
		{
			new_word = 1;
			if (str[i] >= '0' && str[i] <= '9')
			{
				new_word = 0;
			}
		}
		i++;
	}
	return (str);
}
