/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:08:22 by akent-go          #+#    #+#             */
/*   Updated: 2023/08/09 17:04:09 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

char	*get_heredoc_str(char *str[2], size_t len, char *lim, char *warning)
{
	char	*tmp;

	while (g_status != 130 && (!str[0] || ft_strncmp(str[0], lim, len) \
			|| ft_strlen(lim) != len))
	{
		tmp = str[1];
		str[1] = ft_strjoin(str[1], str[0]);
		free (tmp);
		free (str[0]);
		str[0] = readline("> ");
		if (!str[0])
		{
			printf("%s (wanted `%s\')\n", warning, lim);
			break ;
		}
		tmp = str[0];
		str[0] = ft_strjoin(str[0], "\n");
		free (tmp);
		len = ft_strlen(str[0]) - 1;
	}
	free (str[0]);
	return (str[1]);
}

/*
 * This function works as a heredoc, creating a 
 new prompt and sending the characters
 * received to an especific file descriptor
 */

int	get_heredoc(char *str[2], char *aux[2])
{
	int	fd[2];

	g_status = 0;
	if (pipe(fd) == -1)
	{
		ms_error(PIPERROR, NULL, 1);
		return (-1);
	}
	str[1] = get_heredoc_str(str, 0, aux[0], aux[1]);
	write(fd[WRITE_FD], str[1], ft_strlen(str[1]));
	free (str[1]);
	close(fd[WRITE_FD]);
	if (g_status == 130)
	{
		close(fd[READ_FD]);
		return (-1);
	}
	return (fd[READ_FD]);
}
