/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:06:53 by akent-go          #+#    #+#             */
/*   Updated: 2023/07/30 18:06:53 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

/*
 *	This function is used to get our file descriptors properly
 */

int	get_fd(int oldfd, char *path, int flag[2])
{
	int	fd;

	if (oldfd > 2)
		close (oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !flag[0])
		ms_error(NODIR, path, 127);
	else if (!flag[0] && access(path, R_OK) == -1)
		ms_error(NOPERM, path, 126);
	else if (flag[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		ms_error(NOPERM, path, 126);
	if (flag[0] && flag[1])
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flag[0] && !flag[1])
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flag[0] && oldfd != -1)
		fd = open (path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

/*
 *	This function is used when we get >> in our commands
 */

t_ms	*get_of_concat(t_ms *node, char **args, int *i)
{
	char	*new_line;
	int		flag[2];

	flag[0] = 1;
	flag[1] = 1;
	new_line = "El Nano🇪🇸 : syntax error near unexpected token `newline'";
	(*i)++;
	if (args[++(*i)])
		node->outfile = get_fd(node->outfile, args[*i], flag);
	if (!args[*i] || node->outfile == -1)
	{
		*i = -1;
		if (node->outfile != -1)
		{
			ft_putendl_fd(new_line, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

/*
 * This function is used when we get > in our commands
 */

t_ms	*get_of_redir(t_ms *node, char **args, int *i)
{
	char	*new_line;
	int		flag[2];

	flag[0] = 1;
	flag[1] = 0;
	new_line = "El Nano🇪🇸 : syntax error near unexpected token `newline'";
	(*i)++;
	if (args[(*i)])
		node->outfile = get_fd(node->outfile, args[*i], flag);
	if (!args[*i] || node->outfile == -1)
	{
		*i = -1;
		if (node->outfile != -1)
		{
			ft_putendl_fd(new_line, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

t_ms	*get_inf_redir(t_ms *node, char **args, int *i)
{
	char	*new_line;
	int		flag[2];

	flag[0] = 0;
	flag[1] = 0;
	new_line = "El Nano🇪🇸 : syntax error near unexpected token `newline'";
	(*i)++;
	if (args[(*i)])
		node->infile = get_fd(node->infile, args[*i], flag);
	if (!args[*i] || node->infile == -1)
	{
		*i = -1;
		if (node->infile != -1)
		{
			ft_putendl_fd(new_line, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

t_ms	*get_inf_heredoc(t_ms *node, char **args, int *i)
{
	char	*aux[2];
	char	*new_line;
	char	*str[2];

	str[0] = NULL;
	str[1] = NULL;
	aux[0] = NULL;
	aux[1] = "El Nano🇪🇸 : warning: here-document delimited by end-of-file";
	new_line = "El Nano🇪🇸 : syntax error near unexpected token `newline'";
	(*i)++;
	if (args[++(*i)])
	{
		aux[0] = args[*i];
		node->infile = get_heredoc(str, aux);
	}
	if (!args[*i] || node->infile == -1)
	{
		*i = -1;
		if (node->infile != -1)
		{
			ft_putendl_fd(new_line, 2);
			g_status = 2;
		}
	}
	return (node);
}
