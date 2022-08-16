/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_complite.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:25:16 by lallison          #+#    #+#             */
/*   Updated: 2022/05/11 16:25:19 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	doing_execve(t_com **node)
{
	if (access((*node)->exe[0], X_OK))
	{
		write(2, "Nyash-Bash: ", 12);
		write(2, (*node)->exe[0], ft_strlen((*node)->exe[0]));
		write(2, ": command not found\n", 20);
	}
	execve((*node)->exe[0], (*node)->exe, g_n.envp);
	exit (127);
}

void	first_part(t_com **node, int *i)
{
	if (!(*node)->builtin_flag)
	{
		g_n.pid[*i] = fork();
		if (!g_n.pid[*i])
		{
			if ((*node)->fd_in > 0)
				dup2((*node)->fd_in, 0);
			else if (*i > 0)
				dup2(g_n.fd[1][0], 0);
			if ((*node)->fd_out > 0)
				dup2((*node)->fd_out, 1);
			else if (*i < g_n.size - 1)
				dup2(g_n.fd[0][1], 1);
			close(g_n.fd[0][0]);
			close(g_n.fd[0][1]);
			doing_execve(node);
		}
	}
	close(g_n.fd[0][1]);
	if (*i > 0)
		close(g_n.fd[1][0]);
	*node = (*node)->next;
	(*i)++;
}

void	second_part(t_com **node, int *i)
{
	if (!(*node)->builtin_flag)
	{
		pipe(g_n.fd[1]);
		g_n.pid[*i] = fork();
		if (!g_n.pid[*i])
		{
			close(g_n.fd[1][0]);
			if ((*node)->fd_in > 0)
				dup2((*node)->fd_in, 0);
			else if (*i > 0)
				dup2(g_n.fd[0][0], 0);
			if ((*node)->fd_out > 0)
				dup2((*node)->fd_out, 1);
			else if (*i < g_n.size - 1)
				dup2(g_n.fd[1][1], 1);
			close(g_n.fd[0][0]);
			close(g_n.fd[1][1]);
			doing_execve(node);
		}
		close(g_n.fd[0][0]);
		close(g_n.fd[1][1]);
		*node = (*node)->next;
		(*i)++;
	}
}

void	builtin_command(t_com **node, int *i, int *fd)
{
	if (*node && (*node)->builtin_flag)
	{
		g_n.exit_status = 0;
		if (!ft_strcmp((*node)->exe[0], "echo"))
			echo_builtin(node, fd, i, 1);
		else if (!ft_strcmp((*node)->exe[0], "cd"))
			cd_builtin(node, -1, i);
		else if (!ft_strcmp((*node)->exe[0], "pwd"))
			pwd_builtin(node, fd, i);
		else if (!ft_strcmp((*node)->exe[0], "export"))
			export_builtin(node, fd, i);
		else if (!ft_strcmp((*node)->exe[0], "unset"))
			unset_builtin(node, i, fd, 0);
		if (!ft_strcmp((*node)->exe[0], "env"))
			env_builtin(node, fd, i, -1);
		else if (!ft_strcmp((*node)->exe[0], "exit"))
		{
			exit_builtin(node);
			return ;
		}
		*node = (*node)->next;
		(*i)++;
		if (*node)
			second_part(node, i);
	}
}

void	command_complete(t_com **final)
{
	int		i;
	t_com	*tmp;

	tmp = *final;
	g_n.size = lst_size_pipe(final, 0);
	if (g_n.size > 1)
		find_and_replace_exit(final);
	g_n.pid = malloc(sizeof(int) * g_n.size);
	signal(SIGINT, signal_in_process);
	signal(SIGQUIT, signal_in_process);
	i = 0;
	while (i < g_n.size)
	{
		pipe(g_n.fd[0]);
		builtin_command(&tmp, &i, g_n.fd[0]);
		if (tmp)
			first_part(&tmp, &i);
		if (tmp)
			second_part(&tmp, &i);
	}
	close(g_n.fd[0][0]);
	global_waiting();
}
