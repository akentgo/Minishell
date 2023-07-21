#include "includes/minishell.h"

void	child_builtin(t_read *prompt, t_ms *m, int l, t_list *cmd)
{
	//
	//
	if (!is_builtin(m) && m->cmd)
		execve(m->path, m->path, prompt->env);
	else if (m->cmd && !ft_strncmp(*m->cmd, "pwd", l) && l == 3)
		g_status = ms_pwd();
	else if (is_builtin(m) && m->cmd && !ft_strncmp(*m->cmd, "echo", l) && \
			l == 4)
		g_status = ms_echo(cmd);
	else if (is_builtin(m) && m->cmd && !ft_strncmp(*m->cmd, "env", l) && \
			l == 3)
	{
		g_status = 0;
		print_env(prompt->env);
	}
}

static void	*child_redir(t_list *cmd, int fd[2])
{
	t_ms	*node;
	
	node = cmd->content;
	if (node->infile != STDIN_FILENO)
	{
		if (dup2(node->infile, STDIN_FILENO == -1))
			return (ms_error(DUPERROR, NULL, 1));
		close(node->infile);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if(dup2(node->outfile, STDOUT_FILENO) == -1)
			return (ms_error(DUPERROR, NULL, 1));
		close(node->outfile);
	}
	else if (cmd->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (ms_error(DUPERROR, NULL, 1));
	close(fd[WRITE_END]);
	return ("");
}

void	*child_process(t_read *p, t_list *cmd, int fd[2])
{
	t_ms	*m;
	int		l;

	m = cmd->content;
	l = 0;
	if (n->cmd)
	l = ft_strlen(*n->cmd);
	child_redir(cmd, fd);
	close(fd[READ_END]);
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
		close(fd[READ_END]);
		close(fd[WRITE_END]);
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