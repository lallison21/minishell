/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:53:48 by lallison          #+#    #+#             */
/*   Updated: 2022/05/15 15:53:50 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	token_checker(const char *str, int i, int flag)
{
	if ((str[i] == '>' || str[i] == '<') && !flag)
	{
		if (str[i] != str[i + 1] && (str[i + 1] == '>' || str[i + 1] == '<'
				|| str[i + 1] == '|'))
			return (1);
		if (str[i] == str[i + 1])
			if (str[i + 2] == '>' || str[i + 2] == '<' || str[i + 2] == '|')
				return (2);
		i++;
	}
	else if (str[i] == '|' && !flag)
	{
		if (str[i + 1] == '|')
			return (0);
	}
	if (after_spaces(str, i))
		return (3);
	return (0);
}

void	change_wildcard(t_com **node, const char *wildcard, const char *ls)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (wildcard[i] && ls[j])
	{
		if (wildcard[i] == ls[j] && (wildcard[i + 1] == ls[j + 1]
				|| wildcard[i + 1] == '*'))
		{
			j++;
			i++;
		}
		else
			j++;
		if (wildcard[i] == '*' && wildcard[i + 1])
			i++;
	}
	if (wildcard[i] == '*' && !wildcard[i + 1])
		i++;
	if (!wildcard[i] && !ls[j])
		fill_com(node, (char *)ls);
}

void	replace_wildcard(t_com **old, t_com **new)
{
	t_com	*next;
	t_com	*curr;

	next = (*old)->next;
	curr = *new;
	(*old)->cmd = ft_strdup(curr->cmd, (*old)->cmd);
	free((*new)->cmd);
	free(*new);
	if (!curr->next)
		return ;
	curr = curr->next;
	(*old)->next = curr;
	while (curr->next)
		curr = curr->next;
	curr->next = next;
}

void	wildcard_parsing(t_com	**node)
{
	DIR				*pwd;
	struct dirent	*ls;
	char			*wildcard;
	t_com			*new;

	pwd = opendir(".");
	ls = readdir(pwd);
	wildcard = ft_strdup((*node)->cmd, NULL);
	new = NULL;
	while (ls)
	{
		if (!((ls->d_name[0] == '.' && ls->d_name[1] == '.')
				|| ls->d_name[0] == '.'))
			change_wildcard(&new, wildcard, ls->d_name);
		ls = readdir(pwd);
	}
	closedir(pwd);
	if (new)
		replace_wildcard(node, &new);
	new = NULL;
	free(wildcard);
}

void	check_wildcard(t_com **node)
{
	int		i;
	t_com	*tmp;

	tmp = *node;
	i = -1;
	while (tmp)
	{
		i = -1;
		while (tmp->cmd[++i])
			if (tmp->cmd[i] == '*')
				wildcard_parsing(&tmp);
		tmp = tmp->next;
	}
}
