#include "includes/minishell.h"

extern int	g_status;

/*
 * This function check if the command is a builtin and send it to execute
 */

//Hay que hacer las builtins
int	builtin(t_read *prompt, t_list *cmd, int *is_exit, int n)
{
	char	**s;
	int		i;

	while (cmd)
	{
		i = 0;
		s = ((t_ms *)cmd->content)->cmd;
		n = 0;
		if (s)
			n = ft_strlen(*s);
		if (s && !ft_strncmp(*s, "exit", n) && n == 4)
			g_status = ms_exit(cmd, is_exit);
		else if (!cmd->next && s && !ft_strncmp(*s, "cd", n) && n == 2)
			g_status = ms_cd(prompt);
		else if (!cmd->next && s && !ft_strncmp(*s, "export", n) && n == 6)
		{
			if (!s[i + 1])
				print_empty_env(prompt->env);
			i--;
			while (s[++i])
				ms_export(prompt->env, s[i], 0);
		}
		else if (!cmd->next && s && !ft_strncmp(*s, "unset", n) && n == 5)
		{
			while (s[++i])
				ms_unset(prompt->env, s[i]);
		}
		else if (!cmd->next && s && !ft_strncmp(*s, "env", n) && n == 3)
			print_env(prompt->env);
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			exec_cmd(prompt, cmd);
		}
		if((!ft_strncmp(*s, "export", n) && n == 6) || (!ft_strncmp(*s, "unset", n) && n == 5))
			g_status = 0;
		cmd = cmd->next;
	}
	return (g_status);
}

int	ms_exit(t_list *cmd, int *is_status)
{
	printf("Eh estoy en ms_exit\n");
	return (1);
}

int	is_builtin(t_ms *m)
{
	int	len;

	if (!m->cmd) //if there is no command return 0
		return (0);
	if ((m->cmd && ft_strchr(*m->cmd, '/')) || (m->path && \
		ft_strchr(m->path, '/'))) //if there is command and it has '/' or there is a path and it has '/' return 0
		return (0);
	len = ft_strlen(*m->cmd); //set len to the command length
	// check if the command is a builtin and the length is correct for each builtin
	if (!ft_strncmp(*m->cmd, "pwd", len) && len == 3)
		return (1);
	if (!ft_strncmp(*m->cmd, "env", len) && len == 3)
		return (1);
	if (!ft_strncmp(*m->cmd, "cd", len) && len == 2)
		return (1);
	if (!ft_strncmp(*m->cmd, "export", len) && len == 6)
		return (1);
	if (!ft_strncmp(*m->cmd, "unset", len) && len == 5)
		return (1);
	if (!ft_strncmp(*m->cmd, "echo", len) && len == 4)
		return (1);
	if (!ft_strncmp(*m->cmd, "exit", len) && len == 4)
		return (1);
	return (0); // in case it is not a builtin return 0
}
