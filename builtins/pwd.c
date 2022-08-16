/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:22:19 by lallison          #+#    #+#             */
/*   Updated: 2022/05/17 12:22:20 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_builtin(t_com **node, int *fd, int const *i)
{
	int	std_out;

	if (g_n.fd[1][0])
		close(g_n.fd[1][0]);
	std_out = dup(1);
	if ((*node)->fd_out > 0)
		dup2((*node)->fd_out, 1);
	else if (*i < g_n.size - 1)
		dup2(fd[1], 1);
	printf("%s\n", find_env_val("PWD"));
	g_n.exit_status = 0;
	dup2(std_out, 1);
	if (*i == g_n.size - 1)
		close(fd[0]);
	close(fd[1]);
}
