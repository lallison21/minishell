/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:29:24 by lallison          #+#    #+#             */
/*   Updated: 2022/04/26 18:29:26 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	insert_new_node(t_com *lst, int *i)
{
	t_com	*tmp;
	char	*str;

	str = ft_substr(lst->cmd, 0, *i, 0);
	if (ft_strlen(str))
	{
		tmp = lstnew(ft_substr(lst->cmd, (*i)++, ft_strlen(lst->cmd), 1));
		lst->cmd = ft_substr(str, 0, ft_strlen(str), 1);
	}
	else
	{
		free(str);
		if (lst->cmd[*i + 1] == lst->cmd[*i])
		{
			tmp = lstnew(ft_substr(lst->cmd, *i + 2, ft_strlen(lst->cmd), 0));
			lst->cmd = ft_substr(lst->cmd, 0, (*i)++ + 2, 1);
		}
		else
		{
			tmp = lstnew(ft_substr(lst->cmd, *i + 1, ft_strlen(lst->cmd), 0));
			lst->cmd = ft_substr(lst->cmd, 0, *i + 1, 1);
		}
	}
	tmp->next = lst->next;
	lst->next = tmp;
}

int	lst_size_pipe(t_com **node, int pipe_flag)
{
	int		size;
	t_com	*tmp;

	size = 0;
	if (!*node)
		return (size);
	tmp = *node;
	while (tmp)
	{
		if (pipe_flag && tmp->pipe_flag)
			break ;
		if (tmp->cmd || tmp->exe)
			size++;
		tmp = tmp->next;
	}
	return (size);
}

void	final_node_fill(t_com **node)
{
	t_com	*tmp;
	int		i;

	tmp = g_n.com;
	i = 0;
	(*node)->exe = malloc(sizeof(char *) * lst_size_pipe(&g_n.com, 1) + 1);
	while (tmp && !tmp->pipe_flag)
	{
		if (tmp->cmd)
			(*node)->exe[i++] = ft_strdup(tmp->cmd, tmp->cmd);
		tmp->cmd = NULL;
		tmp = tmp->next;
	}
	g_n.fd_in = -2;
	g_n.fd_out = -2;
	(*node)->cmd = NULL;
	(*node)->next = NULL;
	(*node)->exe[i] = NULL;
	fill_or_and_flag(node);
	(*node)->pipe_flag = 0;
	(*node)->parenthesis = 0;
	(*node)->quotes_flag = 0;
	(*node)->builtin_flag = 0;
	(*node)->fd_in = g_n.fd_in;
	(*node)->fd_out = g_n.fd_out;
}

void	set_builtin_flag(t_com **node)
{
	t_com	*tmp;

	tmp = *node;
	while (tmp)
	{
		if (!ft_strcmp(tmp->exe[0], "echo") || !ft_strcmp(tmp->exe[0], "exit")
			|| !ft_strcmp(tmp->exe[0], "pwd") || !ft_strcmp(tmp->exe[0], "env")
			|| !ft_strcmp(tmp->exe[0], "export")
			|| !ft_strcmp(tmp->exe[0], "cd")
			|| !ft_strcmp(tmp->exe[0], "unset"))
			tmp->builtin_flag = 1;
		tmp = tmp->next;
	}
}

void	global_waiting(void)
{
	int		i;
	int		wstatus;

	i = -1;
	while (++i < g_n.size)
		waitpid(g_n.pid[i], &g_n.exit_status, 0);
	if (WIFEXITED(wstatus))
		g_n.exit_status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(g_n.pid[i]))
	{
		g_n.exit_status = WTERMSIG(g_n.exit_status);
		if (g_n.exit_status != 131 && g_n.exit_status != 0)
			g_n.exit_status += 128;
	}
	free(g_n.pid);
}
