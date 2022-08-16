/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 08:51:07 by                   #+#    #+#             */
/*   Updated: 2021/10/13 12:39:42 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_slices(char const *s, char c)
{
	int	i;
	int	slices;

	i = 0;
	slices = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			slices++;
		i++;
	}
	return (slices);
}

void	*ft_mem_error(char **str, int slices)
{
	int	i;

	i = 0;
	while (i < slices)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

int	ft_len_slices(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	return (len);
}

char	**ft_fill_slices(char const *s, char c, int slices, char **str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (i < slices)
	{
		while (*s == c)
			s++;
		len = ft_len_slices(s, c);
		str[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!str[i])
			return (ft_mem_error(str, slices));
		j = 0;
		while (j < len)
		{
			str[i][j] = *s;
			j++;
			s++;
		}
		str[i][j] = '\0';
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		slices;

	if (!s)
		return (NULL);
	slices = ft_slices(s, c);
	str = (char **)malloc(sizeof(char *) * (slices + 1));
	if (!str)
		return (NULL);
	str = ft_fill_slices(s, c, slices, str);
	return (str);
}
