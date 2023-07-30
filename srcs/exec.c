/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:56:12 by akent-go          #+#    #+#             */
/*   Updated: 2023/07/30 17:56:13 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_builtin(t_read *p, t_ms *n, int l, t_list *cmd)
{
	char	**envs;

	envs = turn_into_arr(p->env);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!is_builtin(n) && n->cmd)
		execve(n->path, n->cmd, envs);
	else if (n->cmd && !ft_strncmp(*n->cmd, "pwd", l) && l == 3)
		g_status = ms_pwd();
	else if (is_builtin(n) && n->cmd && !ft_strncmp(*n->cmd, "echo", l) && \
			l == 4)
		g_status = ms_echo(cmd);
	else if (is_builtin(n) && n->cmd && !ft_strncmp(*n->cmd, "env", l) && \
			l == 3)
	{
		g_status = 0;
		print_env(p->env);
	}
	ft_free_matrix(&envs);
}

static void	*child_redir(t_list *cmd, int fd[2])
{
	t_ms	*n;

	n = cmd->content;
	if (n->infile != INFILE)
	{
		if (dup2(n->infile, INFILE) == -1)
			return (ms_error(DUPERROR, NULL, 1));
		close(n->infile);
	}
	if (n->outfile != OUTFILE)
	{
		if (dup2(n->outfile, OUTFILE) == -1)
			return (ms_error(DUPERROR, NULL, 1));
		close(n->outfile);
	}
	else if (cmd->next && dup2(fd[WRITE_FD], OUTFILE) == -1)
		return (ms_error(DUPERROR, NULL, 1));
	close(fd[WRITE_FD]);
	return ("");
}

void	*child_process(t_read *p, t_list *cmd, int fd[2])
{
	t_ms	*n;
	int		l;

	n = cmd->content;
	l = 0;
	if (n->cmd)
		l = ft_strlen(*n->cmd);
	child_redir(cmd, fd);
	close(fd[READ_FD]);
	child_builtin(p, n, l, cmd);
	ft_lstclear(&p->cmd, free_cmd);
	exit(g_status);
}

void	exec_fork(t_read *p, t_list *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[READ_FD]);
		close(fd[WRITE_FD]);
		ms_error(FORKERROR, NULL, 1);
	}
	else if (!pid)
		child_process(p, cmd, fd);
}

void	*check_to_fork(t_read *p, t_list *cmd, int fd[2])
{
	t_ms	*n;
	DIR		*dir;

	n = cmd->content;
	dir = NULL;
	if (n->cmd)
		dir = opendir(*n->cmd);
	if (n->infile == -1 || n->outfile == -1)
		return (NULL);
	if ((n->path && access(n->path, X_OK) == 0) || is_builtin(n))
		exec_fork(p, cmd, fd);
	else if (!is_builtin(n) && ((n->path && !access(n->path, F_OK)) || dir))
		g_status = 126;
	else if (!is_builtin(n) && n->cmd)
		g_status = 127;
	if (dir)
		closedir(dir);
	return ("");
}
