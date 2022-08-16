/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:27:46 by lallison          #+#    #+#             */
/*   Updated: 2022/04/12 10:27:48 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pipes_redirect(const char *str, int i)
{
	int	flag;
	int	status;

	flag = 0;
	status = 0;
	if (str[0] == '|' || str[0] == '&' || str[ft_strlen(str) - 1] == '|'
		|| str[ft_strlen(str) - 1] == '>' || str[ft_strlen(str) - 1] == '<'
		|| str[ft_strlen(str) - 1] == '&')
		status = 1;
	while (str[++i] && !status)
	{
		flag = set_flag(str[i], flag);
		if (token_checker(str, i, flag))
			status = 1;
	}
	if (status)
	{
		printf("Nyash-Bash: syntax error near unexpected token `|' or`<'"
			" or `&'\n");
		g_n.exit_status = 1;
	}
	return (status);
}

int	check_quotes(const char *line, int i)
{
	int	flag;
	int	parenthesis;

	flag = 0;
	parenthesis = 0;
	while (line[++i])
	{
		if (line[i] == SING_QUOTES && flag == 0)
			flag = 1;
		else if (line[i] == DOUB_QUOTES && flag == 0)
			flag = 2;
		else if ((line[i] == SING_QUOTES && flag == 1)
			|| (line[i] == DOUB_QUOTES && flag == 2))
			flag = 0;
		else if (line[i] == '(')
			parenthesis++;
		else if (line[i] == ')')
			parenthesis--;
	}
	if (parenthesis_quotes_error(flag, parenthesis))
		return (1);
	return (0);
}

int	check_symbol(t_com *tmp, int i)
{
	if (!ft_strcmp(tmp->cmd, "<<") || !ft_strcmp(tmp->cmd, ">>")
		|| !ft_strcmp(tmp->cmd, "<") || !ft_strcmp(tmp->cmd, ">")
		|| !ft_strcmp(tmp->cmd, "|") || !ft_strcmp(tmp->cmd, "||")
		|| !ft_strcmp(tmp->cmd, "&&"))
		return (1);
	else if (tmp->cmd[i] == '<' || tmp->cmd[i] == '>' || tmp->cmd[i] == '|'
		|| tmp->cmd[i] == '&')
		return (2);
	return (0);
}

int	check_right(char *str)
{
	if (check_quotes(str, -1))
		return (1);
	if (check_pipes_redirect(str, -1))
		return (2);
	return (0);
}

char	*set_line_status(void)
{
	char	*line;

	if (!g_n.exit_status)
		line = readline(GREEN"➜"BEGIN"  Nyash-Bash "CLOSE);
	else
		line = readline(RED"➜"BEGIN"  Nyash-Bash "CLOSE);
	return (line);
}
