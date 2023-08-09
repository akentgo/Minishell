/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:50:35 by akent-go          #+#    #+#             */
/*   Updated: 2023/07/30 17:50:36 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	ms_error2(int err_code, char *param, int err)
{
	if (err_code == PIPENDERROR)
		ft_putstr_fd("El Nano🇪🇸 : syntax error near unexpected token `|'\n", 2);
	else if (err_code == MEM)
		ft_putstr_fd("El Nano🇪🇸 : not memory left on device\n", 2);
	else if (err_code == IS_DIR)
		ft_putstr_fd("El Nano🇪🇸 : Is a directory: ", 2);
	else if (err_code == NOT_DIR)
		ft_putstr_fd("El Nano🇪🇸 : Not a directory: ", 2);
	else if (err_code == 12)
		ft_putstr_fd("El Nano🇪🇸 : Not a valid identifier: ", 2);
}

/*
 *	This function prints the error message
 */
void	*ms_error(int err_code, char *param, int err)
{
	g_status = err;
	if (err_code == QUOTE)
		ft_putstr_fd("El Nano🇪🇸 : error while looking for matching quote", 2);
	else if (err_code == NODIR)
		ft_putstr_fd("El Nano🇪🇸 : No such file or directoy: ", 2);
	else if (err_code == NOPERM)
		ft_putstr_fd("El Nano🇪🇸 : permission denied: ", 2);
	else if (err_code == NCMD)
		ft_putstr_fd("El Nano🇪🇸 : command not found: ", 2);
	else if (err_code == DUPERROR)
		ft_putstr_fd("El Nano🇪🇸 : dup2 failed", 2);
	else if (err_code == FORKERROR)
		ft_putstr_fd("El Nano🇪🇸 : fork failed\n", 2);
	else if (err_code == PIPERROR)
		ft_putstr_fd("El Nano🇪🇸 : error creating pipe\n", 2);
	else
		ms_error2(err_code, param, err);
	ft_putendl_fd(param, 2);
	return (0);
}

int	ms_exit(t_list *cmd, int *ex)
{
	t_ms	*n;
	long	status[2];

	n = cmd->content;
	*ex = !cmd->next;
	if (*ex)
		ft_putstr_fd("exit\n", 2);
	if (!n->cmd || !n->cmd[1])
		return (0);
	status[1] = ft_atoi_mod(n->cmd[1], &status[0]);
	if (status[1] == -1)
	{
		ft_putstr_fd("El Nano🇪🇸 : exit: ", 2);
		ft_putstr_fd(n->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	else if (n->cmd[2])
	{
		*ex = 0;
		ft_putstr_fd("El Nano🇪🇸 : exit: too many arguments\n", 2);
		return (1);
	}
	status[0] %= 256 + 256 * (status[0] < 0);
	return (status[0]);
}

/*
 *	This function will check for errors during cd execution
 */
void	cd_error(char **str[2])
{
	DIR	*dir;

	dir = NULL;
	if (str[0][1])
		dir = opendir(str[0][1]);
	if (!str[0][1] && str[1][0] && !str[1][0][0])
	{
		g_status = 1;
		ft_putstr_fd("minishell: HOME not set\n", 2);
	}
	if (str[1][0] && !str[0][1])
		g_status = chdir(str[1][0]) == -1;
	if (str[0][1] && dir && access(str[0][1], F_OK) != -1)
		chdir(str[0][1]);
	else if (str[0][1] && access(str[0][1], F_OK) == -1)
		ms_error(NODIR, str[0][1], 1);
	else if (str[0][1])
		ms_error(NOT_DIR, str[0][1], 1);
	if (str[0][1] && dir)
		closedir(dir);
}

/*
 *	This function will free completely a node from our cmd list
 */

void	free_cmd(void *cmd)
{
	t_ms	*node;

	node = cmd;
	ft_free_matrix(&node->cmd);
	free (node->path);
	if (node->infile != INFILE)
		close(node->infile);
	if (node->outfile != OUTFILE)
		close(node->outfile);
	free (node);
}
