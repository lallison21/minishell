/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 10:42:22 by                   #+#    #+#             */
/*   Updated: 2022/01/11 16:07:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*first_arg(char const *s2)
{
	int		i;
	char	*str;

	i = -1;
	str = malloc(sizeof(char) * (ft_strlen(s2) +1));
	if (!str)
		return (NULL);
	while (s2[++i])
		str[i] = s2[i];
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2, int f1, int f2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
		return (first_arg(s2));
	if (!s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) +1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	if (f1)
		free((char *)s1);
	if (f2)
		free((char *)s2);
	return (str);
}
