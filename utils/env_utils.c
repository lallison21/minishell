/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:14:12 by lallison          #+#    #+#             */
/*   Updated: 2022/05/03 18:14:14 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**char_env(void)
{
	int		len;
	char	**envp;
	t_env	*env;

	len = 0;
	env = g_n.env;
	while (env)
	{
		len++;
		env = env->next;
	}
	envp = malloc(sizeof(char *) * len + 1);
	if (!envp)
		exit (12);
	env = g_n.env;
	len = 0;
	while (env)
	{
		envp[len] = ft_strjoin(env->name, "=", 0, 0);
		envp[len] = ft_strjoin(envp[len], env->val, 1, 0);
		len++;
		env = env->next;
	}
	envp[len] = NULL;
	return (envp);
}

char	*find_env(char *str, int j)
{
	t_env	*tmp;

	tmp = g_n.env;
	if (!ft_strcmp(str + j + 1, "?"))
		return (ft_itoa(g_n.exit_status));
	while (tmp)
	{
		if (!ft_strncmp(str + j + 1, tmp->name, len_dollar(str + j) - 1))
			return (ft_strdup(tmp->val, NULL));
		tmp = tmp->next;
	}
	return (NULL);
}

void	fill_env(t_env **node, char *env)
{
	t_env	*tmp;
	t_env	*curr;

	tmp = malloc(sizeof(t_env));
	if (!tmp)
		exit(1);
	tmp->name = before_equals(env);
	if (ft_strcmp(tmp->name, "SHLVL"))
		tmp->val = after_equals(env);
	else
		tmp->val = change_shlvl(after_equals(env));
	tmp->next = NULL;
	if (!*node)
	{
		*node = tmp;
		return ;
	}
	curr = *node;
	while (curr->next)
		curr = curr->next;
	curr->next = tmp;
}

void	deallocate_env(t_env **node)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = *node;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2->val);
		free(tmp2->name);
		free(tmp2);
	}
	node = NULL;
}

char	*find_env_val(char *name)
{
	t_env	*tmp;

	tmp = g_n.env;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
			return (tmp->val);
		tmp = tmp->next;
	}
	return (NULL);
}
