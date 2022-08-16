/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_and_parenthesis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:59:57 by lallison          #+#    #+#             */
/*   Updated: 2022/05/23 18:59:59 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_continue(t_com *tmp)
{
	if (tmp)
	{
		if (tmp->flag_or > tmp->flag_and && g_n.exit_status)
			command_complete_loop(&tmp);
		else if (tmp->flag_or > tmp->flag_and && !g_n.exit_status)
		{
			while (tmp && (tmp->flag_or > tmp->flag_and || tmp->parenthesis))
				tmp = tmp->next;
			if (tmp)
				command_complete_loop(&tmp);
		}
		else if (tmp->flag_and > tmp->flag_or && !g_n.exit_status)
			command_complete_loop(&tmp);
		else if (tmp->flag_and > tmp->flag_or && g_n.exit_status)
		{
			while (tmp && (tmp->flag_and > tmp->flag_or || tmp->parenthesis))
				tmp = tmp->next;
			if (tmp)
				command_complete_loop(&tmp);
		}
	}
}

void	command_complete_loop(t_com **final)
{
	int		or;
	int		and;
	t_com	*tmp;
	t_com	*new_final;

	or = (*final)->flag_or;
	and = (*final)->flag_and;
	tmp = *final;
	new_final = NULL;
	fucking_norminette(&new_final, &tmp, or, and);
	command_complete(&new_final);
	deallocate(&new_final);
	check_continue(tmp);
}

int	parenthesis_loop(int i, int j, int *parenthesis, t_com *curr)
{
	if (*parenthesis)
		curr->parenthesis = *parenthesis;
	while (curr->exe[i][++j])
	{
		if (curr->exe[i][j] == '(')
		{
			if (i == 0 && j == 0)
				(*parenthesis)++;
			else
				return (1);
		}
		else if (curr->exe[i][j] == ')')
		{
			if (curr->exe[i + 1] == NULL && curr->exe[i][j + 1] == '\0')
				(*parenthesis)--;
			else
				return (2);
		}
		else if (*parenthesis > 1)
			return (3);
	}
	return (0);
}

void	trim_parenthesis(t_com **final)
{
	int		i;
	int		j;
	t_com	*curr;

	curr = *final;
	while (curr)
	{
		i = -1;
		while (curr->exe[++i])
		{
			j = -1;
			while (curr->exe[i][++j])
			{
				if (curr->exe[i][j] == '(')
					curr->exe[i] = ft_strdup(curr->exe[i] + 1, curr->exe[i]);
				else if (curr->exe[i][j] == ')')
					curr->exe[i] = ft_substr(curr->exe[i], 0,
							ft_strlen(curr->exe[i]) - 1, 1);
			}
		}
		curr = curr->next;
	}
}

int	trim_parenthesis_and_set_flag(t_com **final)
{
	int		i;
	t_com	*curr;
	int		parenthesis;

	parenthesis = 0;
	curr = *final;
	while (curr)
	{
		i = -1;
		while (curr->exe[++i])
		{
			if (parenthesis_loop(i, -1, &parenthesis, curr))
				return (1);
		}
		if (parenthesis)
			curr->parenthesis = parenthesis;
		curr = curr->next;
	}
	trim_parenthesis(final);
	return (0);
}
