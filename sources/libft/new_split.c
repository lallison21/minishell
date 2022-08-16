/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:07:28 by lallison          #+#    #+#             */
/*   Updated: 2022/03/28 13:07:32 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	skip_quotes(char const *s, char c, int i)
{
	int	skip;

	skip = i + 1;
	while (s[skip] != c && s[skip] != '\0')
		skip++;
	if (s[skip] == '\0')
		return (i);
	return (skip);
}

int	how_much(char const *s, char c)
{
	int		i;
	int		slices;

	i = -1;
	slices = 0;
	while (s[++i])
	{
		if ((s[i] == DOUB_QUOTES || s[i] == SING_QUOTES))
			i = skip_quotes(s, s[i], i);
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			slices++;
	}
	return (slices);
}

char	**fill_slices(char const *s, char c, int slices, char **str)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < slices)
	{
		while (*s == c)
			s++;
		if (*s == DOUB_QUOTES || *s == SING_QUOTES)
			len = len_quotes(s, *s, c) + 1;
		else
			len = len_slices(s, c);
		str[i] = malloc(sizeof(char) * (len + 1));
		if (!str[i])
			return (ft_mem_error(str, slices));
		j = -1;
		while (++j < len)
			str[i][j] = *s++;
		str[i][j] = '\0';
	}
	str[i] = NULL;
	return (str);
}

char	**new_split(char const *s, char c)
{
	char	**str;
	int		slices;

	if (!s)
		return (NULL);
	slices = how_much(s, c);
	str = malloc(sizeof(char *) * (slices + 1));
	if (!str)
		return (NULL);
	str = fill_slices(s, c, slices, str);
	return (str);
}
