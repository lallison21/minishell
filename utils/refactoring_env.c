/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactoring_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 15:29:19 by lallison          #+#    #+#             */
/*   Updated: 2022/05/29 15:29:22 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_path(t_env **env)
{
	t_env	*tmp;
	t_env	*path;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PATH"))
			return ;
		tmp = tmp->next;
	}
	path = malloc(sizeof(t_env));
	path->name = ft_strdup("PATH", NULL);
	path->val = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", NULL);
	path->next = *env;
	*env = path;
}

void	check_home(t_env **env)
{
	t_env	*tmp;
	t_env	*home;
	char	*true_home;

	true_home = home_path();
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "HOME"))
		{
			if (ft_strcmp(tmp->val, true_home))
			{
				tmp->val = ft_strdup(true_home, tmp->val);
				free(true_home);
				return ;
			}
		}
		tmp = tmp->next;
	}
	home = malloc(sizeof(t_env));
	home->name = ft_strdup("HOME", NULL);
	home->val = ft_strdup(true_home, NULL);
	home->next = *env;
	*env = home;
	free(true_home);
}

void	check_user(t_env **env)
{
	t_env	*tmp;
	t_env	*user;
	char	*true_user;

	true_user = user_path();
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "USER"))
		{
			if (ft_strcmp(tmp->val, true_user))
			{
				tmp->val = ft_strdup(true_user, tmp->val);
				free(true_user);
				return ;
			}
		}
		tmp = tmp->next;
	}
	user = malloc(sizeof(t_env));
	user->name = ft_strdup("USER", NULL);
	user->val = ft_strdup(true_user, NULL);
	user->next = *env;
	*env = user;
	free(true_user);
}

void	check_pwd(t_env **env)
{
	t_env	*tmp;
	t_env	*pwd;
	char	*true_pwd;

	true_pwd = getcwd(NULL, 0);
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PWD"))
		{
			if (ft_strcmp(tmp->val, true_pwd))
			{
				tmp->val = ft_strdup(true_pwd, tmp->val);
				free(true_pwd);
				return ;
			}
		}
		tmp = tmp->next;
	}
	pwd = malloc(sizeof(t_env));
	pwd->name = ft_strdup("PWD", NULL);
	pwd->val = ft_strdup(true_pwd, NULL);
	pwd->next = *env;
	*env = pwd;
	free(true_pwd);
}

void	check_oldpwd(t_env **env)
{
	t_env	*tmp;
	t_env	*oldpwd;
	char	*true_oldpwd;

	true_oldpwd = getcwd(NULL, 0);
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "OLDPWD"))
		{
			if (ft_strcmp(tmp->val, true_oldpwd))
			{
				tmp->val = ft_strdup(true_oldpwd, tmp->val);
				free(true_oldpwd);
				return ;
			}
		}
		tmp = tmp->next;
	}
	oldpwd = malloc(sizeof(t_env));
	oldpwd->name = ft_strdup("OLDPWD", NULL);
	oldpwd->val = ft_strdup(true_oldpwd, NULL);
	oldpwd->next = *env;
	*env = oldpwd;
	free(true_oldpwd);
}
