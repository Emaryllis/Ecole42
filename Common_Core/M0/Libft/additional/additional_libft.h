/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:40:26 by egoh              #+#    #+#             */
/*   Updated: 2025/09/11 20:55:09 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ADDITIONAL_LIBFT_H
# define ADDITIONAL_LIBFT_H
# include "../libft.h"

int		ft_endswith(const char *str, const char *suffix, size_t str_len);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strstr(const char *haystack, const char *needle);
#endif