/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:38:24 by lallison          #+#    #+#             */
/*   Updated: 2022/04/12 10:38:25 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_node(t_node *node)
{
	node->size = 0;
	node->fd_in = -2;
	node->com = NULL;
	node->line = NULL;
	node->fd_out = -2;
	node->flag_or = 0;
	node->final = NULL;
	node->flag_and = 0;
}

void	fill_com(t_com **root, char *str)
{
	t_com	*tmp;
	t_com	*curr;

	tmp = malloc(sizeof(t_com));
	tmp->cmd = ft_substr(str, 0, ft_strlen(str), 0);
	tmp->exe = NULL;
	tmp->fd_in = -2;
	tmp->next = NULL;
	tmp->flag_or = 0;
	tmp->fd_out = -2;
	tmp->flag_and = 0;
	tmp->pipe_flag = 0;
	tmp->quotes_flag = 0;
	tmp->builtin_flag = 0;
	tmp->parenthesis = 0;
	if (!*root)
	{
		*root = tmp;
		return ;
	}
	curr = *root;
	while (curr->next)
		curr = curr->next;
	curr->next = tmp;
}

t_com	*lstnew(char *str)
{
	t_com	*node;

	node = malloc(sizeof(t_com));
	if (!node)
		exit(8);
	node->cmd = str;
	node->exe = NULL;
	node->fd_in = -2;
	node->fd_out = -2;
	node->flag_and = 0;
	node->flag_or = 0;
	node->pipe_flag = 0;
	node->quotes_flag = 0;
	node->builtin_flag = 0;
	node->parenthesis = 0;
	node->next = NULL;
	return (node);
}

void	deallocate(t_com **com)
{
	t_com	*tmp;
	t_com	*tmp2;
	int		i;

	tmp = *com;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		if (tmp2->cmd)
			free(tmp2->cmd);
		if (tmp2->exe)
		{
			i = -1;
			while (tmp2->exe[++i])
				free(tmp2->exe[i]);
		}
		free(tmp2->exe);
		free(tmp2);
	}
	*com = NULL;
}

void	split_pipe_or_redirect(void)
{
	int		i;
	int		flag;
	t_com	*tmp;

	tmp = g_n.com;
	while (tmp)
	{
		flag = 0;
		i = -1;
		if (check_symbol(tmp, i))
		{
			tmp = tmp->next;
			continue ;
		}
		while (tmp->cmd[++i])
		{
			flag = set_flag(tmp->cmd[i], flag);
			if (check_symbol(tmp, i) && flag == 0)
			{
				insert_new_node(tmp, &i);
				break ;
			}
		}
		tmp = tmp->next;
	}
}
