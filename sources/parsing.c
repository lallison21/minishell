/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:37:36 by lallison          #+#    #+#             */
/*   Updated: 2022/05/03 18:37:37 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*heredoc_parsing(t_com **node)
{
	char	*str;
	char	*res;
	int		pipe1[2];

	res = NULL;
	while (1)
	{
		str = readline("heredoc> ");
		if (!ft_strcmp(str, (*node)->next->cmd))
			break ;
		if (!str)
			return (free(res), free((*node)->cmd), NULL);
		res = ft_strjoin(res, "\n", 1, 0);
		res = ft_strjoin(res, str, 1, 1);
	}
	res = ft_strjoin(res, "\n", 1, 0);
	pipe(pipe1);
	write(pipe1[1], res, ft_strlen(res));
	g_n.fd_in = pipe1[0];
	close(pipe1[1]);
	close(pipe1[0]);
	free((*node)->next->cmd);
	(*node)->next->cmd = NULL;
	return (free(str), free(res), free((*node)->cmd), NULL);
}

char	*redirect_parsing(t_com **node, int flag)
{
	if (flag == 1)
	{
		g_n.fd_out = open((*node)->next->cmd, O_WRONLY | O_CLOEXEC
				| O_TRUNC | O_CREAT, 0644);
		if (g_n.fd_out == -1)
			return (perm_error(node), free((*node)->cmd), NULL);
	}
	else if (flag == 2)
	{
		g_n.fd_out = open((*node)->next->cmd, O_WRONLY | O_CLOEXEC
				| O_APPEND | O_CREAT, 0644);
		if (g_n.fd_out == -1)
			return (perm_error(node), free((*node)->cmd), NULL);
	}
	else if (flag == 3)
	{
		g_n.fd_in = open((*node)->next->cmd, O_RDONLY, O_CLOEXEC);
		if (g_n.fd_in == -1)
			return (perm_error(node), free((*node)->cmd), NULL);
	}
	else if (flag == 4)
		(*node)->cmd = heredoc_parsing(node);
	free((*node)->next->cmd);
	(*node)->next->cmd = NULL;
	return (free((*node)->cmd), NULL);
}

char	*pipe_parsing(t_com **node, t_com **fin)
{
	t_com	*tmp;
	t_com	*curr;

	tmp = malloc(sizeof(t_com));
	if (!tmp)
		exit (13);
	final_node_fill(&tmp);
	if (!*fin)
	{
		*fin = tmp;
		return (free((*node)->cmd), NULL);
	}
	curr = *fin;
	while (curr->next)
		curr = curr->next;
	curr->next = tmp;
	return (free((*node)->cmd), NULL);
}

void	find_path(t_com **node, int i)
{
	t_com	*tmp;
	char	**paths;
	char	*path;

	paths = ft_split(find_env_val("PATH"), ':');
	tmp = *node;
	while (tmp && paths)
	{
		i = -1;
		while (paths[++i] && !tmp->builtin_flag)
		{
			path = ft_strjoin(paths[i], "/", 0, 0);
			path = ft_strjoin(path, tmp->exe[0], 1, 0);
			if (!access(path, X_OK))
			{
				tmp->exe[0] = ft_strdup(path, tmp->exe[0]);
				free(path);
				break ;
			}
			free(path);
		}
		tmp = tmp->next;
	}
	free_doub_char(paths);
}

void	begin_parsing(void)
{
	t_com	*tmp;

	tmp = g_n.com;
	while (tmp)
	{
		parsing_loop(&tmp);
		tmp = tmp->next;
	}
	g_n.com->cmd = pipe_parsing(&g_n.com, &g_n.final);
	set_builtin_flag(&g_n.final);
	if (trim_parenthesis_and_set_flag(&g_n.final))
	{
		printf("Nyash-Bash: syntax error with parenthesis\n");
		g_n.exit_status = 1;
		return ;
	}
	find_path(&g_n.final, -1);
	command_complete_loop(&g_n.final);
}

//int j = 1;
//for (t_com *curr = g_n.final; curr != NULL; curr = curr->next)
//{
//for (int i = 0; curr->exe[i] != NULL; i++)
//printf("%d ==> %d: %s or: %d and: %d parenthesis: %d\n",
//j, i, curr->exe[i], curr->flag_or, curr->flag_and, curr->parenthesis);
//j++;
//}
