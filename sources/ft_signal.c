/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 12:42:18 by lallison          #+#    #+#             */
/*   Updated: 2022/04/12 12:42:19 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_in_process(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		signal(SIGINT, signal_in_process);
	}
	if (sig == SIGQUIT)
	{
		write(1, "\n", 1);
		signal(SIGINT, signal_in_process);
	}
}

void	ft_sigint(int sig)
{
	(void) sig;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_n.exit_status = 1;
}

void	ft_signal(void)
{
	struct sigaction	sa;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	sa.sa_handler = ft_sigint;
	sigaction(SIGINT, &sa, NULL);
}
