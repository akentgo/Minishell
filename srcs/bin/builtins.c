/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:37:55 by akent-go          #+#    #+#             */
/*   Updated: 2023/08/09 17:03:29 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

void	builtin_exec(t_read *p, t_list *cmd)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	exec_cmd(p, cmd);
}

int	builtin(t_read *p, t_list *cmd, int *is_exit, int n)
{
	char	**s;

	while (cmd)
	{
		s = ((t_ms *)cmd->content)->cmd;
		if (s)
			n = ft_strlen(*s);
		if (s && !ft_strncmp(*s, "exit", n) && n == 4)
			g_status = ms_exit(cmd, is_exit);
		else if (!cmd->next && s && !ft_strncmp(*s, "cd", n) && n == 2)
			g_status = ms_cd(p);
		else if (!cmd->next && s && !ft_strncmp(*s, "export", n) && n == 6)
			g_status = ms_export(p->env, s, 0);
		else if (!cmd->next && s && !ft_strncmp(*s, "unset", n) && n == 5)
			ms_unset(p->env, s, 0);
		else if (!cmd->next && s && !ft_strncmp(*s, "env", n) && n == 3)
			print_env(p->env);
		else
			builtin_exec(p, cmd);
		cmd = cmd->next;
	}
	return (g_status);
}

int	is_builtin(t_ms *m)
{
	int	len;

	if (!m->cmd)
		return (0);
	if ((m->cmd && ft_strchr(*m->cmd, '/')) || (m->path && \
		ft_strchr(m->path, '/')))
		return (0);
	len = ft_strlen(*m->cmd);
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
	return (0);
}
