/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:33:52 by lallison          #+#    #+#             */
/*   Updated: 2021/10/07 14:55:09 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i])
		;
	return (i);
}

int	len_quotes(char const *s, char q, char c)
{
	int	len;

	len = 1;
	while (s[len] != q && s[len])
		len++;
	if (!s[len])
		return (len_slices(s, c));
	else if (s[len + 1] && s[len + 1] != c)
		len += len_slices(s + len + 1, c);
	return (len);
}

int	len_slices(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] == c)
		len++;
	while (s[len] && s[len] != c)
	{
		len++;
		if (s[len] == DOUB_QUOTES || s[len] == SING_QUOTES)
			len += len_quotes(s + len, s[len], c);
	}
	return (len);
}

int	len_dollar(char *dollar)
{
	int	len;

	if (!dollar)
		return (0);
	if (dollar[1] == '?')
		return (2);
	len = 0;
	while (dollar[len] && dollar[len] != SPCS && dollar[len] != SING_QUOTES
		&& dollar[len] != DOUB_QUOTES && !(dollar[len] > 8 && dollar[len] < 14))
	{
		len++;
		if (dollar[len] == DOLLAR_SIGN)
			break ;
	}
	return (len);
}
