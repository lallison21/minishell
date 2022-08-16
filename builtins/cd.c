/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:53:03 by lallison          #+#    #+#             */
/*   Updated: 2022/05/17 18:53:04 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_pwd(char *dir, int flag)
{
	t_env	*tmp;
	t_env	*curr;

	tmp = malloc(sizeof(t_env));
	if (!tmp)
		exit(19);
	if (!flag)
		tmp->name = ft_strdup("OLDPWD", NULL);
	else
		tmp->name = ft_strdup("PWD", NULL);
	tmp->val = ft_strdup(dir, NULL);
	tmp->next = NULL;
	curr = g_n.env;
	while (curr->next)
		curr = curr->next;
	curr->next = tmp;
}

void	change_pwd(char *dir, int flag, int fr)
{
	t_env	*curr;

	curr = g_n.env;
	if (!flag)
		while (curr && ft_strcmp(curr->name, "OLDPWD"))
			curr = curr->next;
	else
		while (curr && ft_strcmp(curr->name, "PWD"))
			curr = curr->next;
	if (!curr)
		new_pwd(dir, flag);
	else
		curr->val = ft_strdup(dir, curr->val);
	if (fr)
		free(dir);
}

char	*check_dir(char *dir)
{
	if (!ft_strcmp(dir, "~"))
		return (ft_strdup(find_env_val("HOME"), NULL));
	else if (dir[0] == '~' && dir[1] == '/')
		return (ft_strjoin(find_env_val("HOME"), dir + 1, 0, 0));
	else if (!ft_strcmp(dir, "-"))
		return (printf("%s\n", find_env_val("OLDPWD")), find_env_val("OLDPWD"));
	return (dir);
}

void	change_dir(char *path, int i)
{
	char	*dir;
	char	*new_path;

	dir = getcwd(NULL, 0);
	new_path = check_dir(path);
	if (!chdir(new_path))
	{
		change_pwd(dir, 0, 1);
		dir = NULL;
		change_pwd(getcwd(dir, 0), 1, 0);
		while (g_n.envp[++i])
			free(g_n.envp[i]);
		free(g_n.envp);
		g_n.envp = char_env();
	}
	else
	{
		printf("Nyash-Bash: cd: %s: No such file or directory\n", path);
		g_n.exit_status = 1;
	}
	free(dir);
}

void	cd_builtin(t_com **node, int i, int const *j)
{
	char	*path;

	if (g_n.fd[1][0])
		close(g_n.fd[1][0]);
	if ((*node)->exe[1])
		path = ft_strdup((*node)->exe[1], NULL);
	else
		path = ft_strdup(find_env_val("HOME"), NULL);
	if (!path)
	{
		write(2, "Nyash-Bash: cd: HOME not set\n", 29);
		return ;
	}
	if (g_n.size == 1)
		change_dir(path, i);
	if (*j == g_n.size - 1 && !g_n.exit_status)
		close(g_n.fd[0][0]);
	close(g_n.fd[0][1]);
	free(path);
}
