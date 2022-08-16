/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:47:14 by lallison          #+#    #+#             */
/*   Updated: 2022/05/26 19:47:16 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parenthesis_quotes_error(int flag, int parenthesis)
{
	if (flag)
	{
		write(1, "Unclosed quotes marks\n", 22);
		g_n.exit_status = 1;
		return (1);
	}
	if (parenthesis)
	{
		write(1, "Unclosed parenthesis marks\n", 27);
		g_n.exit_status = 1;
		return (1);
	}
	return (0);
}

void	fill_or_and_flag(t_com **node)
{
	if (g_n.flag_and == g_n.flag_or)
	{
		(*node)->flag_and = 0;
		(*node)->flag_or = 0;
	}
	else if (g_n.flag_and > g_n.flag_or)
	{
		(*node)->flag_and = g_n.flag_and;
		(*node)->flag_or = -1;
	}
	else if (g_n.flag_and < g_n.flag_or)
	{
		(*node)->flag_and = -1;
		(*node)->flag_or = g_n.flag_or;
	}
}

void	pipe_utils(t_com **tmp, int flag)
{
	(*tmp)->pipe_flag = 1;
	if (flag == 1)
		(*tmp)->cmd = pipe_parsing(tmp, &g_n.final);
	else if (flag == 2)
	{
		(*tmp)->cmd = pipe_parsing(tmp, &g_n.final);
		if (g_n.flag_or < g_n.flag_and)
			g_n.flag_or = g_n.flag_and + 1;
		else
			g_n.flag_or++;
	}
	else if (flag == 3)
	{
		(*tmp)->cmd = pipe_parsing(tmp, &g_n.final);
		if (g_n.flag_and < g_n.flag_or)
			g_n.flag_and = g_n.flag_or + 1;
		else
			g_n.flag_and++;
	}
	(*tmp)->pipe_flag = 0;
}

void	parsing_loop(t_com **tmp)
{
	if (!ft_strcmp((*tmp)->cmd, ">"))
		(*tmp)->cmd = redirect_parsing(tmp, 1);
	else if (!ft_strcmp((*tmp)->cmd, ">>"))
		(*tmp)->cmd = redirect_parsing(tmp, 2);
	else if (!ft_strcmp((*tmp)->cmd, "<"))
		(*tmp)->cmd = redirect_parsing(tmp, 3);
	else if (!ft_strcmp((*tmp)->cmd, "<<"))
		(*tmp)->cmd = heredoc_parsing(tmp);
	else if (!ft_strcmp((*tmp)->cmd, "|"))
		pipe_utils(tmp, 1);
	else if (!ft_strcmp((*tmp)->cmd, "||"))
		pipe_utils(tmp, 2);
	else if (!ft_strcmp((*tmp)->cmd, "&&"))
		pipe_utils(tmp, 3);
}

int	after_spaces(const char *str, int i)
{
	if ((str[i] == '<' || str[i] == '>') && str[i + 1] == ' ')
	{
		while (str[++i] == ' ')
			;
		if (str[i] == '>' || str[i] == '<' || str[i] == '|' || str[i] == '&'
			|| str[i] == '(' || str[i] == ')')
			return (1);
	}
	else if (str[i] == '|' && str[i + 1] == ' ')
	{
		while (str[++i] == ' ')
			;
		if (str[i] == '>' || str[i] == '<' || str[i] == '|' || str[i] == '&')
			return (2);
	}
	return (0);
}
