/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:22:51 by lallison          #+#    #+#             */
/*   Updated: 2022/04/12 10:22:54 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pre_parser(char *line, int i)
{
	line = ft_strtrim(line, " ");
	if (!ft_strcmp(line, ""))
	{
		g_n.exit_status = 0;
		return ;
	}
	if (check_right(line))
		return ;
	g_n.line = new_split(line, ' ');
	find_dollar();
	while (g_n.line[++i])
		fill_com(&g_n.com, g_n.line[i]);
	split_pipe_or_redirect();
	find_and_trim(&g_n.com);
	check_wildcard(&g_n.com);
	begin_parsing();
	free(line);
	deallocate(&g_n.com);
	deallocate(&g_n.final);
	i = -1;
	while (g_n.line[++i])
		free(g_n.line[i]);
	free(g_n.line);
}

char	*home_path(void)
{
	DIR				*dir;
	char			*res;
	char			*path;
	struct dirent	*entity;

	dir = opendir("/Users");
	if (dir == NULL)
		return (NULL);
	entity = readdir(dir);
	while (entity)
	{
		if (entity->d_name[0] != '.')
		{
			path = ft_strjoin("/Users/", entity->d_name, 0, 0);
			res = ft_strjoin(path, "/Desktop", 0, 0);
			if (!access(res, 4))
				return (free(res), path);
			free(path);
			free(res);
		}
		entity = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}

char	*user_path(void)
{
	DIR				*dir;
	char			*res;
	char			*path;
	struct dirent	*entity;

	dir = opendir("/Users");
	if (dir == NULL)
		return (NULL);
	entity = readdir(dir);
	while (entity)
	{
		if (entity->d_name[0] != '.')
		{
			path = ft_strjoin("/Users/", entity->d_name, 0, 0);
			res = ft_strjoin(path, "/Desktop", 0, 0);
			if (!access(res, 4))
				return (free(path), free(res), ft_strdup(entity->d_name, NULL));
			free(path);
			free(res);
		}
		entity = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}

void	refactoring_env(void)
{
	check_path(&g_n.env);
	check_home(&g_n.env);
	check_user(&g_n.env);
	check_pwd(&g_n.env);
	check_oldpwd(&g_n.env);
}

int	main(int ac, char **av, char **env)
{
	int		i;
	char	*line;

	if (ac != 1)
		exit_av(av);
	read_history("../.history");
	i = -1;
	while (env[++i])
		fill_env(&g_n.env, env[i]);
	refactoring_env();
	g_n.envp = char_env();
	g_n.exit_status = 0;
	while (1)
	{
		ft_signal();
		init_node(&g_n);
		line = set_line_status();
		if (!line)
			return (ft_exit(line));
		if (line[0])
			add_history(line);
		write_history("../.history");
		pre_parser(line, -1);
		free(line);
	}
}
