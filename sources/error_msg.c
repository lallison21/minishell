/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:18:54 by lallison          #+#    #+#             */
/*   Updated: 2022/05/03 18:18:57 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_av(char **av)
{
	if (!access(av[1], F_OK))
		printf("%s: %s: is a file or directory\n", av[1], av[1]);
	else
		printf("Nyash-Bash: %s: No such file or directory\n", av[1]);
	exit(127);
}

int	ft_exit(char *line)
{
	int	i;

	write(1, "exit\n", 5);
	deallocate_env(&g_n.env);
	i = -1;
	while (g_n.envp[++i])
		free(g_n.envp[i]);
	free(g_n.envp);
	free(line);
	return (g_n.exit_status);
}

int	perm_error(t_com **node)
{
	printf("Nyash-Bash: %s: Permission denied\n", (*node)->next->cmd);
	free((*node)->next->cmd);
	(*node)->next->cmd = NULL;
	return (1);
}
