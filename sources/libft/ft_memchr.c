/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:09:46 by lallison          #+#    #+#             */
/*   Updated: 2021/10/13 16:42:46 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	c1;

	if (!n)
		return (NULL);
	s1 = (unsigned char *)s;
	c1 = (unsigned char)c;
	i = 0;
	while (s1 && i < n)
	{
		if (s1[i] == c1)
			return (&s1[i]);
		i++;
	}
	if (*s1 == '\0' && c == '\0')
		return (s1);
	return (NULL);
}
