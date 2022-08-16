/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:03:15 by lallison          #+#    #+#             */
/*   Updated: 2022/05/12 14:03:17 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_builtin(t_com **node)
{
	int	ex;

	write(2, "exit\n", 5);
	if ((*node)->exe[1])
	{
		ex = ft_atoi((*node)->exe[1]);
		if (ex == -1)
		{
			write(2, "Nyash-Bash: exit: ", 18);
			write(2, (*node)->exe[1], ft_strlen((*node)->exe[1]));
			write(2, ": numeric argument required\n", 28);
			exit(255);
		}
		else
			exit(ex);
	}
	exit(g_n.exit_status);
}

void	find_and_replace_exit(t_com **node)
{
	int		i;
	t_com	*tmp;

	tmp = *node;
	while (tmp)
	{
		if (!ft_strcmp(tmp->exe[0], "exit"))
		{
			i = 0;
			while (tmp->exe[i])
				free(tmp->exe[i++]);
			free(tmp->exe);
			tmp->builtin_flag = 0;
			tmp->exe = NULL;
		}
		tmp = tmp->next;
	}
}
