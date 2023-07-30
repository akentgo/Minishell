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

//bueno, aqui he cambiado lo de READ_END y WRITE_END y he puesto lo que me ha salido de la picha👍🏻
void	exec_custom(char ***out, char *cmd, char *arg, char **env)
{
	pid_t	pid;
	int		fd[2];
	char	**splitted;

	pipe(fd); //pipe the file descriptor
	pid = fork(); //assign the process id using fork
	if (!pid) //if pid is 0, so we are in the parent process do...
	{
		close(fd[0]); //close read part of the pipe
		splitted = (ft_split(arg, ' ')); //split the argument so we have it word by word
		dup2(fd[1], STDOUT_FILENO); // assign 1 to the writing fd
		close(fd[1]); //close the writing fd
		if (!access(cmd, F_OK)) //if the command is accessible, execute it and return (execve returns itself)
			execve(cmd, splitted, env);
		exit(1); //if the command failed return 1
	}
	close(fd[1]); //close writing fd
	waitpid(pid, NULL, 0);
	update_output(out, fd[0]);
	close(fd[0]);
}
