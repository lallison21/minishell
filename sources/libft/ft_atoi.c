/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 10:22:02 by lallison          #+#    #+#             */
/*   Updated: 2022/01/12 14:06:57 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check(long int res)
{
	while (res < 0)
		res += 256;
	while (res > 255)
		res -= 256;
	return (res);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			neg;
	long int	res;

	neg = 1;
	res = 0;
	i = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
		if (str[i++] == '-')
			neg *= -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + neg * (str[i] - '0');
		i++;
		if (neg == 1 && res < 0 && i > 20)
			return (-1);
		if (neg == -1 && res > 0 && i > 19)
			return (-1);
	}
	if (str[i])
		return (-1);
	return (check(res));
}
