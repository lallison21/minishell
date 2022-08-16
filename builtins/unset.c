/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:14:20 by lallison          #+#    #+#             */
/*   Updated: 2022/05/17 16:14:22 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_element(t_env **env, int flag)
{
	if (!flag)
	{
		free((*env)->name);
		free((*env)->val);
		*env = (*env)->next;
	}
	else
	{
		free((*env)->next->name);
		free((*env)->next->val);
		(*env)->next = (*env)->next->next;
	}
}

void	unset_builtin(t_com **node, int const *i, int *fd, int j)
{
	t_env	*tmp;

	if (g_n.fd[1][0])
		close(g_n.fd[1][0]);
	while ((*node)->exe[++j] && g_n.size == 1)
	{
		tmp = g_n.env;
		if (!ft_strcmp(tmp->name, (*node)->exe[j]))
			remove_element(&tmp, 0);
		while (tmp->next)
		{
			if (!ft_strcmp(tmp->next->name, (*node)->exe[j]))
			{
				remove_element(&tmp, 1);
				continue ;
			}
			tmp = tmp->next;
		}
	}
	free_doub_char(g_n.envp);
	g_n.envp = char_env();
	if (*i == g_n.size - 1)
		close(fd[0]);
	close(fd[1]);
}
