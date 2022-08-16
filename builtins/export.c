/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:08:00 by lallison          #+#    #+#             */
/*   Updated: 2022/05/19 20:10:49 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export_sorting(t_env *env)
{
	t_env	*curr;
	char	*tmp;

	curr = env;
	while (curr->next)
	{
		if (ft_strcmp(curr->name, curr->next->name) > 0)
		{
			tmp = curr->name;
			curr->name = curr->next->name;
			curr->next->name = tmp;
			tmp = curr->val;
			curr->val = curr->next->val;
			curr->next->val = tmp;
			curr = env;
		}
		else
			curr = curr->next;
	}
	curr = env;
	while (curr)
	{
		printf("declare -x %s=\"%s\"\n", curr->name, curr->val);
		curr = curr->next;
	}
}

int	replace_elem(char *str)
{
	int		len;
	t_env	*curr;

	curr = g_n.env;
	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	if (!str[len])
		return (1);
	while (curr)
	{
		if (!ft_strncmp(curr->name, str, len))
		{
			curr->val = ft_strdup(str + len + 1, curr->val);
			return (0);
		}
		curr = curr->next;
	}
	return (2);
}

void	new_elem_in_env(t_com **node, int i)
{
	while ((*node)->exe[++i])
	{
		if (!replace_elem((*node)->exe[i]))
			continue ;
		if ((*node)->exe[i][0] == '_'
		|| ((*node)->exe[i][0] >= 'A' && (*node)->exe[i][0] <= 'Z')
		|| ((*node)->exe[i][0] >= 'a' && (*node)->exe[i][0] <= 'z'))
		{
			if (!ft_strchr((*node)->exe[i], '='))
				continue ;
			else
				env_add_back(&g_n.env, (*node)->exe[i]);
		}
		else
		{
			printf("Nyash-Bash: export: `%s': not a valid identifier\n",
				(*node)->exe[i]);
			g_n.exit_status = 1;
		}
	}
	i = -1;
	while (g_n.envp[++i])
		free(g_n.envp[i]);
	free(g_n.envp);
	g_n.envp = char_env();
}

void	sort_and_print_export(t_com **node, int std_out, int *fd, int const *i)
{
	t_env	*cpy;
	t_env	*curr;

	curr = g_n.env;
	cpy = NULL;
	while (curr)
	{
		copy_env(&cpy, curr->name, curr->val);
		curr = curr->next;
	}
	if ((*node)->fd_out > 0)
		dup2((*node)->fd_out, 1);
	else if (*i < g_n.size - 1)
		dup2(fd[1], 1);
	export_sorting(cpy);
	dup2(std_out, 1);
	close(fd[1]);
	deallocate_env(&cpy);
}

void	export_builtin(t_com **node, int *fd, int const *i)
{
	int		std_out;

	if (g_n.fd[1][0])
		close(g_n.fd[1][0]);
	std_out = dup(1);
	if (!(*node)->exe[1])
		sort_and_print_export(node, std_out, fd, i);
	else if (g_n.size == 1)
		new_elem_in_env(node, 0);
	if (*i == g_n.size - 1)
		close(fd[0]);
	g_n.exit_status = 0;
}
