/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:14:07 by lallison          #+#    #+#             */
/*   Updated: 2022/04/14 14:14:09 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_flag(char c, int flag)
{
	if (c == SING_QUOTES && flag == 0)
		flag = 1;
	else if (c == DOUB_QUOTES && flag == 0)
		flag = 2;
	else if ((c == DOUB_QUOTES && flag == 2)
		|| (c == SING_QUOTES && flag == 1))
		flag = 0;
	return (flag);
}

int	how_quotes(const char *line)
{
	int	i;
	int	q;
	int	flag;

	q = 0;
	i = -1;
	flag = 0;
	while (line[++i])
	{
		if (!flag && line[i] == SING_QUOTES)
			flag = 1;
		else if (!flag && line[i] == DOUB_QUOTES)
			flag = 2;
		else if ((line[i] == SING_QUOTES && flag == 1)
			|| (line[i] == DOUB_QUOTES && flag == 2))
		{
			flag = 0;
			q += 2;
		}
	}
	return (q);
}

char	*trim_quotes(t_com *com, int i, int j, int flag)
{
	char	*str;
	char	*res;

	str = com->cmd;
	res = malloc(sizeof(char) * ft_strlen(str) - how_quotes(str) + 1);
	if (!res)
		exit(5);
	while (str[++i])
	{
		if (str[i] == SING_QUOTES && flag == 0)
			flag = 1;
		else if (str[i] == DOUB_QUOTES && flag == 0)
			flag = 2;
		else if ((str[i] == SING_QUOTES && flag == 1)
			|| (str[i] == DOUB_QUOTES && flag == 2))
		{
			flag = 0;
			com->quotes_flag = 1;
		}
		else
			res[++j] = str[i];
	}
	res[++j] = '\0';
	free(com->cmd);
	return (res);
}

void	find_and_trim(t_com **root)
{
	int		i;
	t_com	*tmp;

	tmp = *root;
	while (tmp)
	{
		i = -1;
		while (tmp->cmd[++i])
		{
			if (tmp->cmd[i] == SING_QUOTES || tmp->cmd[i] == DOUB_QUOTES)
			{
				tmp->cmd = trim_quotes(tmp, -1, -1, 0);
				break ;
			}
		}
		tmp = tmp->next;
	}
}
