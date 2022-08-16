/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equals_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 11:23:56 by lallison          #+#    #+#             */
/*   Updated: 2022/04/12 11:23:58 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*change_shlvl(char *val)
{
	char	*res;

	if (!ft_atoi(val))
	{
		res = "1";
		free(val);
		return (res);
	}
	else if (ft_atoi(val) == 999)
	{
		res = "";
		free(val);
		return (res);
	}
	else
	{
		res = ft_itoa(ft_atoi(val) + 1);
		free(val);
		return (res);
	}
}

char	*before_equals(char *env)
{
	int		i;
	char	*res;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		exit(2);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		res[i] = env[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*after_equals(const char *env)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	j = i + 1;
	while (env[j])
		j++;
	res = malloc(sizeof(char) * j - i + 1);
	if (!res)
		exit(3);
	j = 0;
	i++;
	while (env[i])
		res[j++] = env[i++];
	res[j] = '\0';
	return (res);
}

void	copy_env(t_env	**env, char *name, char *val)
{
	t_env	*tmp;
	t_env	*curr;

	tmp = malloc(sizeof(t_env));
	if (!tmp)
		exit(16);
	tmp->name = ft_strdup(name, NULL);
	tmp->val = ft_strdup(val, NULL);
	tmp->next = NULL;
	if (!*env)
	{
		*env = tmp;
		return ;
	}
	curr = *env;
	while (curr->next)
		curr = curr->next;
	curr->next = tmp;
}

void	env_add_back(t_env **env, char *content)
{
	t_env	*tmp;
	t_env	*curr;

	tmp = malloc(sizeof(t_env));
	if (!tmp)
		exit(17);
	tmp->name = before_equals(content);
	tmp->val = after_equals(content);
	tmp->next = NULL;
	curr = *env;
	while (curr->next)
		curr = curr->next;
	curr->next = tmp;
}
