/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:05:25 by lallison          #+#    #+#             */
/*   Updated: 2022/04/12 15:05:26 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_dollar(char *str, int i, int j)
{
	int		len;
	char	*res;
	char	*tmp;

	tmp = find_env(str, j);
	len = ft_strlen(str) - len_dollar(str + j) + ft_strlen(tmp);
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		exit(4);
	i = 0;
	len = 0;
	while (str[len] && str[len] != DOLLAR_SIGN)
		res[i++] = str[len++];
	len += len_dollar(str + j);
	j = 0;
	if (tmp)
		while (tmp[j])
			res[i++] = tmp[j++];
	free(tmp);
	while (str[len])
		res[i++] = str[len++];
	res[i] = '\0';
	free(str);
	return (res);
}

void	find_dollar(void)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	while (g_n.line[++i])
	{
		flag = 0;
		j = -1;
		while (g_n.line[i][++j])
		{
			flag = set_flag(g_n.line[i][j], flag);
			if (g_n.line[i][j] == DOLLAR_SIGN && (flag == 0 || flag == 2))
			{
				g_n.line[i] = check_dollar(g_n.line[i], i, j);
				j = -1;
				flag = 0;
			}
		}
	}
}

void	free_doub_char(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
