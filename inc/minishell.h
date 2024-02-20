/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:18:24 by ayblin            #+#    #+#             */
/*   Updated: 2022/07/26 14:29:40 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

extern int	g_exit_code;

# define NRM  "\x1B[0m"
# define RED  "\x1B[31m"
# define GRN  "\x1B[32m"
# define YEL  "\x1B[33m"
# define BLU  "\x1B[34m"
# define MAG  "\x1B[35m"
# define CYN  "\x1B[36m"
# define WHT  "\x1B[37m"

typedef struct s_tab
{
	char			*str;
	struct s_tab	*next;
}			t_tab;

typedef struct s_redirect
{
	char	*cmd;
	char	*here_doc;
	int		fd_out;
	int		fd_in;
	int		idin;
	int		idout;
}		t_redi;

typedef struct s_data
{
	char	**bloc_cmd;
	int		empty_env;
	char	**envi;
}			t_data;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}			t_env;

typedef struct s_pipex
{
	int		save_in;
	int		save_out;
	int		cmd_nbs;
	int		pipe_nbs;
	int		fdin;
	int		fdout;
	int		idx;
	char	*paths;
	char	**mypaths;
	char	*path_from_envp;
	char	*cmd;
	char	**mycmdargs;
	int		here_doc;
}t_pipex;

void		prompt(t_data *data);
void		print_prompt(t_data *data);
void		free_data(t_data *data);

/*----------	my_env.c				----------*/
char		*get_env_var(char **env, char *name);
void		del_env_var(char ***old_env, char *name);
void		add_env_var(char ***old_env, char *name, char *value);
int			find_var(char **env, char *name);
void		update_env_var(char ***old_env, char *name, char *value);

/*----------	ft_strstrutils.c		----------*/
void		ft_freestrstr(char **str);
int			ft_strstrlen(char **str);
char		**ft_strstrdup(char **env);
int			is_empty_str(char *str);

/*----------	replace_vars.c			----------*/
char		*replace_vars(char *str, t_data *data);

/*----------	replace_vars2.c			----------*/
char		*replace_vars2(char *str, t_data *my_data);

/*----------	Builtins				----------*/
int			my_exec(t_data *data, t_pipex p, t_redi **t);
int			ft_pwd(char **args, t_data *data);
int			ft_env(char **args, t_data *data);
int			ft_export(char **args, t_data *data);
int			ft_unset(char **args, t_data *data);
int			ft_cd(char **args, t_data *data);
int			ft_echo(char **args, t_data *data);
void		ft_exit(char **args, t_data *data, t_pipex p, t_redi **t);

/*----------	signal.c				----------*/
void		null_handler(int sigid);
void		sig_handler(int sigid);
// PIPEX .h
int			is_builtin(char *cmd);
int			is_builtin2(char *cmd);
char		*find_path(char **envp);
int			ft_msg(char *str);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		get_infile(char **argv, t_pipex *pipex);
void		get_outfile(char *argv, t_pipex *pipex);
int			here_doc(char *limiter);
void		ft_fds(t_pipex p, pid_t pid, int *pipe_fd, t_redi **t);
int			child(t_pipex *p, t_redi **t, t_data *data);
int			pipex(int argc, t_redi **t, t_data *data);

int			pipex2(int argc, t_redi **t, t_data *data);
int			child2(t_pipex *p, t_redi **t, t_data *data);
//             LST
t_tab		*convert_tab_to_lst(char **tab);
t_tab		*ft_tab_new(char *content);
void		ft_tabadd_back(t_tab **alst, t_tab *new);
t_tab		*ft_tablast(t_tab *lst);
//             PARSING
char		*ft_strjoin2(int size, char **strs, char *sep);
int			parsing(char *str, t_data *data, int i);
char		**ft_splitquotes(char *s, char c);
void		get_redir1(char *str, t_redi *cell_redi);
int			count_len(const char *str);
int			is_quoted(const char *str, int i);
int			uneven_quotes(char *str);
t_redi		*remove_redi(char *str, int i, t_redi *cell_redi, char c);
void		get_redir1(char *str, t_redi *cell_redi);
void		get_redir2(char *str, t_redi *cell_redi);
void		get_redir3(char *str, t_redi *cell_redi);
void		get_redir4(char *str, t_redi *cell_redi);
int			get_redir_len(char *str, int i);
void		get_fd(char *str, char *redi, int i, int len);
void		init_value_redi(t_redi *redi_cell);

//             FREE FUNCTIONS
void		child_free(t_pipex *pipex, t_redi **t, t_data *data);
void		child_free2(t_pipex *pipex, t_redi **t, t_data *data);
void		parent_free(t_pipex *pipex);
char		*free_tab(char **tab);
void		free_cmd_tab(t_redi **r);

void		print_tab(char **tab);
void		print_redi(t_redi *redi);

char		**ft_splitpipe(char *s, char c);

#endif
