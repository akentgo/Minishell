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
		return (mini_perror(DUPERROR, NULL, 1));
	close(fd[WRITE_END]);
	return ("");
}

void	*child_process(t_read *prompt, t_list *cmd, int fd[2])
{
	t_ms	*m;
	int		l;
}
