/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:54:43 by lallison          #+#    #+#             */
/*   Updated: 2022/05/17 11:54:45 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo_builtin(t_com **node, int *fd, int const *i, int j)
{
	int	flag;
	int	std_out;

	if (g_n.fd[1][0])
		close(g_n.fd[1][0]);
	flag = 0;
	if (!ft_strcmp((*node)->exe[j], "-n"))
	{
		j++;
		flag++;
	}
	std_out = dup(1);
	if ((*node)->fd_out > 0)
		dup2((*node)->fd_out, 1);
	else if (*i < g_n.size - 1)
		dup2(fd[1], 1);
	while ((*node)->exe[j])
		printf("%s ", (*node)->exe[j++]);
	if (!flag)
		printf("\n");
	close(fd[1]);
	if (g_n.size - 1 == *i)
		close(fd[0]);
	dup2(std_out, 1);
	g_n.exit_status = 0;
}
