/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lallison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:30:59 by lallison          #+#    #+#             */
/*   Updated: 2022/03/23 18:31:01 by lallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../sources/libft/libft.h"

# define DOUB_QUOTES 34
# define SING_QUOTES 39
# define DOLLAR_SIGN 36
# define CLOSE "\001\033[0m\002"
# define RED "\001\033[49;31m\002"
# define BEGIN "\001\033[49;34m\002"
# define GREEN "\001\033[49;32m\002"

typedef struct s_env
{
	char			*val;
	char			*name;
	struct s_env	*next;
}	t_env;

typedef struct s_com
{
	int				fd_in;
	int				fd_out;
	int				flag_or;
	int				flag_and;
	int				pipe_flag;
	int				quotes_flag;
	int				parenthesis;
	int				builtin_flag;
	char			*cmd;
	char			**exe;
	struct s_com	*next;
}	t_com;

typedef struct s_node
{
	t_env	*env;
	t_com	*com;
	t_com	*final;
	int		size;
	int		*pid;
	int		fd_in;
	int		fd_out;
	int		flag_or;
	int		flag_and;
	int		fd[2][2];
	int		exit_status;
	char	**line;
	char	**envp;
}	t_node;

t_node	g_n;

t_com	*lstnew(char *str);

int		ft_exit(char *line);
int		check_right(char *str);
int		perm_error(t_com **node);
int		set_flag(char c, int flag);
int		check_symbol(t_com *tmp, int i);
int		after_spaces(const char *str, int i);
int		lst_size_pipe(t_com **node, int pipe_flag);
int		trim_parenthesis_and_set_flag(t_com **final);
int		token_checker(const char *str, int i, int flag);
int		parenthesis_quotes_error(int flag, int parenthesis);

char	*home_path(void);
char	*user_path(void);
char	**char_env(void);
char	*set_line_status(void);
char	*change_shlvl(char *val);
char	*before_equals(char *env);
char	*find_env_val(char *name);
char	*find_env(char *str, int j);
char	*after_equals(const char *env);
char	*pipe_parsing(t_com **node, t_com **fin);

void	ft_signal(void);
void	find_dollar(void);
void	exit_av(char **av);
void	begin_parsing(void);
void	global_waiting(void);
void	check_pwd(t_env **env);
void	check_path(t_env **env);
void	check_home(t_env **env);
void	check_user(t_env **env);
void	deallocate(t_com **com);
void	init_node(t_node *node);
void	check_oldpwd(t_env **env);
void	parsing_loop(t_com **tmp);
void	exit_builtin(t_com **node);
void	signal_in_process(int sig);
void	free_doub_char(char **str);
void	find_and_trim(t_com **root);
void	check_wildcard(t_com **node);
void	deallocate_env(t_env **node);
void	split_pipe_or_redirect(void);
void	pre_parser(char *line, int i);
void	final_node_fill(t_com **node);
void	set_builtin_flag(t_com **node);
void	fill_or_and_flag(t_com **node);
char	*heredoc_parsing(t_com **node);
void	command_complete(t_com **final);
void	fill_com(t_com **root, char *str);
void	fill_env(t_env **node, char *env);
void	pipe_utils(t_com **node, int flag);
void	find_and_replace_exit(t_com **node);
void	insert_new_node(t_com *lst, int *i);
void	command_complete_loop(t_com **final);
void	env_add_back(t_env **env, char *content);
char	*redirect_parsing(t_com **node, int flag);
void	copy_env(t_env	**env, char *name, char *val);
void	cd_builtin(t_com **node, int i, int const *j);
void	pwd_builtin(t_com **node, int *fd, int const *i);
void	export_builtin(t_com **node, int *fd, int const *i);
void	env_builtin(t_com **node, int *fd, int const *i, int j);
void	echo_builtin(t_com **node, int *fd, int const *i, int j);
void	unset_builtin(t_com **node, int const *i, int *fd, int j);
void	fucking_norminette(t_com **new_final, t_com **tmp, int or, int and);

#endif
