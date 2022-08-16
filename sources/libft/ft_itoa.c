/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:54:43 by                   #+#    #+#             */
/*   Updated: 2021/10/11 19:12:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sizen(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	else if (n == -2147483648)
		return (11);
	else if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_nbrtostr(char *res, int i, int n)
{
	res[i--] = 0;
	if (n == 0)
		res[i] = '0';
	else if (n < 0)
	{
		res[0] = '-';
		if (n == -2147483648)
		{
			res[1] = '2';
			n = 147483648;
		}
		else
			n *= -1;
	}
	while (n > 0)
	{
		res[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*res;

	i = ft_sizen(n);
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (0);
	res[i] = '\0';
	res = ft_nbrtostr(res, i, n);
	return (res);
}
