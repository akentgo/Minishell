/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:54:43 by akent-go          #+#    #+#             */
/*   Updated: 2023/08/09 17:03:50 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_command(char **env_path, char *cmd, char *path)
{
	char	*tmp;
	int		i;

	i = -1;
	path = NULL;
	while (env_path && env_path[++i])
	{
		free (path);
		tmp = ft_strjoin(env_path[i], "/");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0)
			break ;
	}
	if (!env_path || !env_path[i])
	{
		free (path);
		return (NULL);
	}
	return (path);
}

static DIR	*cmd_check(t_read *p, t_list *cmd, char ***str, char *path)
{
	t_ms	*n;
	DIR		*dir;

	dir = NULL;
	n = cmd->content;
	if (n && n->cmd)
		dir = opendir(*n->cmd);
	if (n && n->cmd && ft_strchr(*n->cmd, '/') && !dir)
	{
		*str = ft_split(*n->cmd, '/');
		n->path = ft_strdup(*n->cmd);
		free (n->cmd[0]);
		n->cmd[0] = ft_strdup(str[0][ft_matrixlen(*str) - 1]);
	}
	else if (!is_builtin(n) && n && n->cmd && !dir)
	{
		path = search_env(p->env, "PATH");
		*str = ft_split(path, ':');
		if (path)
			free (path);
		n->path = find_command(*str, *n->cmd, n->path);
		if (!n->path || !n->cmd[0] || !n->cmd[0][0])
			ms_error(NCMD, *n->cmd, 127);
	}
	return (dir);
}

void	get_cmd(t_read *p, t_list *cmd, char **str, char *path)
{
	t_ms	*n;
	DIR		*dir;

	n = cmd->content;
	dir = cmd_check(p, cmd, &str, path);
	if (!is_builtin(n) && n && n->cmd && dir)
		ms_error(IS_DIR, *n->cmd, 126);
	else if (!is_builtin(n) && n && n->path && access(n->path, F_OK) == -1)
		ms_error(NODIR, n->path, 127);
	else if (!is_builtin(n) && n && n->path && access(n->path, X_OK) == -1)
		ms_error(NOPERM, n->path, 126);
	if (dir)
		closedir(dir);
	ft_free_matrix(&str);
}

void	*exec_cmd(t_read *p, t_list *cmd)
{
	int	fd[2];

	get_cmd(p, cmd, NULL, NULL);
	if (pipe(fd) == -1)
		return (ms_error(PIPERROR, NULL, 1));
	if (!check_to_fork(p, cmd, fd))
		return (NULL);
	close(fd[WRITE_FD]);
	if (cmd->next && !((t_ms *)cmd->next->content)->infile)
		((t_ms *)cmd->next->content)->infile = fd[READ_FD];
	else
		close(fd[READ_FD]);
	if (((t_ms *)cmd->content)->infile > 2)
		close(((t_ms *)cmd->content)->infile);
	if (((t_ms *)cmd->content)->outfile > 2)
		close(((t_ms *)cmd->content)->outfile);
	return (NULL);
}
