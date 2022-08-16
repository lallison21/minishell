/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:46:11 by lallison          #+#    #+#             */
/*   Updated: 2022/05/28 16:46:12 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**doubly_char(char **exe)
{
	int		i;
	char	**res;

	i = 0;
	while (exe[i])
		i++;
	res = malloc(sizeof(char *) * i + 1);
	i = -1;
	while (exe[++i])
		res[i] = ft_strdup(exe[i], NULL);
	res[i] = NULL;
	return (res);
}

void	fill_new_final_node(t_com **old, t_com **new)
{
	t_com	*tmp;
	t_com	*curr;

	tmp = malloc(sizeof(t_com));
	tmp->fd_in = (*old)->fd_in;
	tmp->fd_out = (*old)->fd_out;
	tmp->flag_or = (*old)->flag_or;
	tmp->flag_and = (*old)->flag_and;
	tmp->pipe_flag = (*old)->pipe_flag;
	tmp->quotes_flag = (*old)->quotes_flag;
	tmp->parenthesis = (*old)->parenthesis;
	tmp->builtin_flag = (*old)->builtin_flag;
	tmp->exe = doubly_char((*old)->exe);
	tmp->cmd = NULL;
	tmp->next = NULL;
	if (!*new)
	{
		*new = tmp;
		return ;
	}
	curr = *new;
	while (curr->next)
		curr = curr->next;
	curr->next = tmp;
}

void	fucking_norminette(t_com **new_final, t_com **tmp, int or, int and)
{
	while (*tmp)
	{
		if (or > and)
		{
			while (*tmp && or == (*tmp)->flag_or)
			{
				fill_new_final_node(tmp, new_final);
				*tmp = (*tmp)->next;
			}
			break ;
		}
		else
		{
			while (*tmp && and == (*tmp)->flag_and)
			{
				fill_new_final_node(tmp, new_final);
				*tmp = (*tmp)->next;
			}
			break ;
		}
	}
}
