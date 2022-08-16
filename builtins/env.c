/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 12:06:16 by lallison          #+#    #+#             */
/*   Updated: 2022/05/14 12:06:18 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_builtin(t_com **node, int *fd, int const *i, int j)
{
	int		std_out;

	if (g_n.fd[1][0])
		close(g_n.fd[1][0]);
	if ((*node)->exe[1])
	{
		write(2, "env: ", 5);
		write(2, (*node)->exe[1], ft_strlen((*node)->exe[1]));
		write(2, ": No such file or directory\n", 28);
		g_n.exit_status = 127;
		return ;
	}
	std_out = dup(1);
	if ((*node)->fd_out > 0)
		dup2((*node)->fd_out, 1);
	else if (*i < g_n.size - 1)
		dup2(fd[1], 1);
	while (g_n.envp[++j])
		printf("%s\n", g_n.envp[j]);
	close(fd[1]);
	if (*i == g_n.size - 1)
		close(fd[0]);
	dup2(std_out, 1);
	g_n.exit_status = 0;
}
