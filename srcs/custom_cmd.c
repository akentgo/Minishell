/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:18:05 by akent-go          #+#    #+#             */
/*   Updated: 2023/07/30 18:18:06 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	update_output(char ***splitted, int fd)
{
	char	**aux;
	char	*tmp;
	char	*line;

	aux = NULL;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_strtrim(line, "\n");
		free (line);
		aux = ft_extend_matrix(aux, tmp);
		free(tmp);
	}
	ft_free_matrix(splitted);
	*splitted = aux;
}

/*
 * This function execute a single command
 */

/*bueno, aqui he cambiado lo de READ_END y 
WRITE_END y he puesto lo que me ha salido de la picha👍🏻*/
void	exec_custom(char ***out, char *cmd, char *arg, char **env)
{
	pid_t	pid;
	int		fd[2];
	char	**splitted;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		splitted = (ft_split(arg, ' '));
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (!access(cmd, F_OK))
			execve(cmd, splitted, env);
		exit(1);
	}
	close(fd[1]);
	waitpid(pid, NULL, 0);
	update_output(out, fd[0]);
	close(fd[0]);
}
