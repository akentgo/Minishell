/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:33:22 by akent-go          #+#    #+#             */
/*   Updated: 2023/07/30 18:33:17 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/ioctl.h>

int	g_status;

///////// ERROR CODES //////
# define QUOTE 1
# define NODIR 2
# define NOPERM 3
# define NOCMD 4
# define DUPERROR 5
# define FORKERROR 6
# define PIPERROR 7
# define PIPENDERROR 8
# define MEM 9
# define IS_DIR 10
# define NOT_DIR 11
# define REDIRERROR 12
# define NCMD 13
# define INFILE 0
# define OUTFILE 1
# define READ_FD 0
# define WRITE_FD 1

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_read
{
	t_list	*cmd;
	t_env	*env;
	pid_t	pid;
}			t_read;

typedef struct s_ms
{
	char	**cmd;
	char	*path;
	int		infile;
	int		outfile;
}			t_ms;

//CD.C//
int				ms_cd(t_read *p);

//ECHO.C//
int				ms_echo(t_list *cmd);

//PWD.C//
int				ms_pwd(void);

//ENVS.C//
t_env			*new_env(void);
void			env_fill(t_env **list, char **env);
char			*set_var(char *name, char *value);
t_env			*env_set(char **env);

//ENV_UTILS.C//
void			unset_helper(t_env *env, char *str);
int				ms_unset(t_env *env, char **str, int i);
void			export_helper(t_env *env, char **str);
int				ms_export(t_env *env, char **str, int i);
void			export_last_cmd(t_env *env, char *s1, char *s2);

//ENV_UTILS2.C
void			ft_free_env(t_env *env);
char			**ft_split_env(char *str);
int				print_empty_env(t_env *env);
void			print_env(t_env *env, char *cmd);
void			print_var(t_env *env, char *str);

//ENV_UTILS3.C
int				env_size(char **env);
int				ms_export1(t_env *env, char *str);
char			*env_parser(char *str, char *sep);

//ENVS_SEARCH//
int				ft_strchr_i(const char *s, int c);
char			*search_env(t_env *env, char *var);
char			*search_env_len(t_env *env, char *var, int n);

//ARGS.C//
char			**ft_matrix_append(char ***big, char **small, int n);
static char		**split_all(char **args, t_read *p);
static void		*parse_args(char **args, t_read *p);
void			*check_args(char *out, t_read *p);

//BUILTINS.C//
void			builtin_exec(t_read *p, t_list *cmd);
int				builtin(t_read *p, t_list *cmd, int *ex, int n);
int				is_builtin(t_ms *m);

//CMD_NODES.C//
t_ms			*ms_init(void);
t_list			*clear_ms(t_list *cmd, char **args, char **tmp);
char			**cmd_trim(char	**args);
t_ms			*get_redir(t_ms *node, char **a[2], int *i);
void			check_redir_caller(char **a[2], int *i);

//CMD_NODES_UTILS.C//
void			check_redir_in(char **a[2], int *i);
void			check_redir_out(char **a[2], int *i);
t_list			*ms_fill(char **args, int i);
char			**ft_expand_arr(char **in, char *new);

//ERROR.C//
void			ms_error2(int err_code, char *param, int err);
void			*ms_error(int err_code, char *param, int err);
int				ms_exit(t_list *cmd, int *ex);
void			cd_error(char **str[2]);
void			free_cmd(void *cmd);

//ERROR_UTILS.C//
void			ft_free_matrix(char ***matrix);
int				ft_matrixlen(char **matrix);
char			**dup_matrix(char **matrix);

//EXEC_CMD.C//
static char		*find_command(char **env_path, char *cmd, char *path);
static DIR		*cmd_check(t_read *p, t_list *cmd, char ***str, char *path);
void			get_cmd(t_read *p, t_list *cmd, char **str, char *path);
void			*exec_cmd(t_read *p, t_list *cmd);

//EXEC.C//
void			child_builtin(t_read *p, t_ms *n, int l, t_list *cmd);
static void		*child_redir(t_list *cmd, int fd[2]);
void			*child_process(t_read *p, t_list *cmd, int fd[2]);
void			exec_fork(t_read *p, t_list *cmd, int fd[2]);
void			*check_to_fork(t_read *p, t_list *cmd, int fd[2]);

//EXPANDER.C//
int				ft_strchr_r(const char *str, char *check);
char			*expand_path(char *str, int i, int qte[2], char *value);
static char		*get_substr(char *str, int i, t_read *rd);
char			*expand_var(char *str, int qte[2], int i, t_read *rd);

//FT_TRIM.C//
static int		trim_len(const char *s);
char			*ft_trim(const char *s, int qte[2]);

//FT_TRIMCMD.C//
static int		n_words(const char *str, char *sep, int ct[2]);
static char		**ft_fill_array(char *str, char **ret, char *sep, int i[3]);
char			**ft_trimcmd(char const *str, char *sep);

//GET_FILES.C//
int				get_fd(int oldfd, char *path, int flag[2]);
t_ms			*get_of_concat(t_ms *node, char **args, int *i);
t_ms			*get_of_redir(t_ms *node, char **args, int *i);
t_ms			*get_inf_redir(t_ms *node, char **args, int *i);
t_ms			*get_inf_heredoc(t_ms *node, char **args, int *i);

//HEREDOC.C//
char			*get_heredoc_str(char *s[2], size_t len, char *lim, char *wn);
int				get_heredoc(char *str[2], char *aux[2]);

//LEXER.C//
char			*ft_strchr(const char *s, int c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				n_words(const char *str, char *sep, int ct[2]);
static char		**ft_fill_array(char *str, char **ret, char *sep, int i[3]);
char			**ft_cmdsplit(char *rd_out, char *sep);

//REDIR_SPLITTER.C//
int				redir_words(char *str, char *sep, int ct);
static char		**ft_fill_redir(char *str, char **ret, char *sep, int i[3]);
char			**redir_split(char *str, char *sep);

//SIGNALS.C//
void			sg_handle(int sig);

//UTILS.C//
int				ft_arealnum(char *str);
char			**turn_into_arr(t_env *envs);
void			ft_strreplace(char **s1, char *s2);
int				ft_strcomp(char *a, char *b);
int				ft_atoi_mod(const char *str, long *l);

#endif
