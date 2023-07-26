#include "includes/minishell.h"

extern int	g_status;

char	*get_heredoc_str(char *str[2], size_t len, char *lim, char *warning)
{
	char	*tmp;

	while (g_status != 130 && (!str[0] || ft_strncmp(str[0], lim, len) \
			|| ft_strlen(lim) != len)) //if our status is 130 and, there is no string, there is no EOF (lim) or the EOF length is not the same as len
	{
		tmp = str[1]; //we hold str[1] in tmp
		str[1] = ft_strjoin(str[1], str[0]); //we join str[1] and str[0] into str[1]
		free (tmp); //free tmp which is a pointer to the old str[1]
		free (str[0]); //free str[0] since we do not need it anymore
		str[0] = readline("> "); //set str[0] to a new prompt since we need to receive something from terminal
		if (!str[0]) //if the string does not exist break the loop
		{
			printf("%s (wanted `%s\')\n", warning, lim);
			break ;
		}
		tmp = str[0]; //hold the new string in tmp;
		str[0] = ft_strjoin(str[0], "\n"); //add a \n to our string
		free (tmp);
		len = ft_strlen(str[0]) - 1; //set len to the length of str[0] - 1
	}
	free (str[0]); //once the loop ends, free str[0] to avoid leaks
	return (str[1]);
}


/*
 * This function works as a heredoc, creating a new prompt and sending the characters
 * received to an especific file descriptor
 */

int	get_heredoc(char *str[2], char *aux[2])
{
	int	fd[2];

	g_status = 0; //set our status to 0
	if (pipe(fd) == -1) //if pipe has an error send error message and return -1 (error)
	{
		ms_error(PIPERROR, NULL, 1);
		return (-1);
	}
	str[1] = get_heredoc_str(str, 0, aux[0], aux[1]); //set str[1] to the string received from get_heredoc_str
	write(fd[WRITE_FD], str[1], ft_strlen(str[1])); //we write in fd[1] the string received
	free (str[1]); //free the string to avoid leaks
	close(fd[WRITE_FD]); //close the fd[1] (writing fd)
	if (g_status == 130) //if the status changed during get_here_doc we close fd[0] (reading fd) and return -1 (error)
	{
		close(fd[READ_FD]);
		return (-1);
	}
	return (fd[READ_FD]); //otherwise return fd[0] (reading fd)
}
