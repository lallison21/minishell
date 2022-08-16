/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:40:34 by                   #+#    #+#             */
/*   Updated: 2021/10/08 14:40:42 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src, char *fr)
{
	int		i;
	int		j;
	char	*str;

	i = ft_strlen(src) + 1;
	str = malloc(sizeof(char) * i);
	if (str == NULL)
		return (NULL);
	j = -1;
	while (++j < i)
		str[j] = src[j];
	str[j] = '\0';
	if (fr)
		free(fr);
	return (str);
}
