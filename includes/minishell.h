/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:33:22 by akent-go          #+#    #+#             */
/*   Updated: 2023/07/19 18:20:42 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>

int g_status;

//pa borra
# define SUCCESS 0
# define FAILURE 1
# define ECHO 2
# define PWD 3
# define UNSET 4
# define SET 5

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

//Structure for enviroment variables, they contain a value and a pointer to the next variable.
typedef struct s_env
{
	char			*name;
	char 			*value;
	struct s_env 	*next;
}	t_env;

typedef struct	s_read
{
	t_list	*cmd;
	t_env	*env;
	pid_t	pid;
}			t_read;

typedef struct	s_ms
{
	char	**cmd; //aqui almacenamos los comandos pasados por parámetro
	char	*path; //Aqui guardamos el path para ejecutar comandos del sistema
	int		infile;
	int		outfile;
}			t_ms;

//ARGS.C//
char	**ft_matrix_append(char ***big, char **small, int n);
static char	**split_all(char **args, t_read *r);
static void	*parse_args(char **args, t_read *r);
void	*check_args(char *out, t_read *p);

//BUILTINS.C//
int	builtin(t_read *prompt, t_list *cmd, int *is_exit, int n);
int	is_builtin(t_ms *m);

//CMD_NODES.C//
static t_ms	*ms_init(void);
static t_list	*clear_ms(t_list *cmd, char **args, char **tmp);
static char	**cmd_trim(char	**args);
static t_ms	*get_redir(t_ms *node, char **a[2], int *i);
void	check_redir_caller(char **a[2], int *i);
void	check_redir_in(char **a[2], int *i);
void	check_redir_out(char **a[2], int *i);
t_list	*ms_fill(char **args, int i);

//CUSTOM_CMD.C//
static void	update_output(char ***splitted, int fd);
void	exec_custom(char ***out, char *cmd, char *arg, char **env);
char	**ft_expand_arr(char **in, char *new);

//ERROR.C//
void	*ms_error(int err_code, char *param, int err);
int		ms_exit(t_list *cmd, int *ex);
void	cd_error(char **str[2]);
void	free_cmd(void *cmd);
int		ft_matrixlen(char **matrix);
void	ft_free_matrix(char ***matrix);
char	**dup_matrix(char **matrix);

//EXEC.C//
void	child_builtin(t_read *prompt, t_ms *m, int l, t_list *cmd);
static void	*child_redir(t_list *cmd, int fd[2]);
void	*child_process(t_read *prompt, t_list *cmd, int fd[2]);

//EXPANDER.C//
void	ft_strreplace(char **s1, char *s2);
int	ft_strchr_r(const char *str, char *check);
char	*expand_path(char *str, int i, int qte[2], char *value);
char	*expand_var(char *str, int qte[2], int i, t_read *rd);

//FT_TRIM.C//
static int	trim_len(const char *s);
char	*ft_trim(const char *s, int qte[2]);

//FT_TRIMCMD.C//
static int n_words(const char *str, char *sep, int ct[2]);
static char	**ft_fill_array(char *str, char **ret, char *sep, int i[3]);
char	**ft_trimcmd(char const *str, char *sep);

//GET_FILES.C//
int	get_fd(int oldfd, char *path, int flag[2]);
t_ms	*get_of_concat(t_ms *node, char **args, int *i);
t_ms	*get_of_redir(t_ms *node, char **args, int *i);
t_ms	*get_inf_redir(t_ms *node, char **args, int *i);
t_ms	*get_inf_heredoc(t_ms *node, char **args, int *i);

//HEREDOC.C//
char	*get_heredoc_str(char *str[2], size_t len, char *lim);
int	get_heredoc(char *str[2], char *aux[2]);

//LEXER.C//
//long	ft_strlen(const char *a);
int	n_words(const char *str, char *sep, int ct[2]);
char	**ft_cmdsplit(char *rd_out, char *sep);

//PROMPT.C//
static char	*get_home(t_read p);
static char	*get_user(t_read p);
char	*ms_getprompt(t_read p);

//REDIT_SPLITTER.C//
int	redir_words(char *str, char *sep, int ct);
static char	**ft_fill_redir(char *str, char **ret, char *sep, int i[3]);
char	**redir_split(char *str, char *sep);

int	builtin(t_read *prompt, t_list *cmd, int *is_exit, int n);
//int ms_cd(t_read *p);
int echo(char **argv);
int ft_pwd(void);

////////////////// ENVIRONMENT MANAGEMENT FUNCTIONS ///////////////////////

//ENV_UTILS2.C//
void    ft_free_env(t_env *env);
char *search_env(t_env *env, char *var);

//ENV_UTILS/////
void    print_all_envs(t_env *env);

//builtin.c
int	builtin(t_read *prompt, t_list *cmd, int *is_exit, int n);

void	ms_export(t_env *env, char *str, int zer);
int		ms_unset(t_env *env, char *str);
int		env_size(char **env);
t_env	*new_env();
void	env_fill(t_env **list, char **env);
int		ft_strcomp(char *a, char *b);
void	print_env(t_env *env);
void	print_var(t_env *env, char *str);
t_env	*env_set(char **env);
char	*search_env(t_env *env, char *var);
char	*search_env_len(t_env *env, char *var, int n);
char    **ft_split_env(char *str);
#endif
