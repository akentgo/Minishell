#include "includes/minishell.h"

extern int	g_status;

/*
 *	This function is used to get our file descriptors properly
 */

int	get_fd(int oldfd, char *path, int flag[2])
{
	int	fd;
	printf("llegamos al fd\n");
	if (oldfd > 2) //if we got an old file descriptor we close it
		close (oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !flag[0]) //if we cannot access to the fd given we return an error
		ms_error(NODIR, path, 127);
	else if (!flag[0] && access(path, R_OK) == -1) //if we cannot read from the fd given we return an error
		ms_error(NOPERM, path, 126);
	else if (flag[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0) //if we can access to the file but we cannot write on it
		ms_error(NOPERM, path, 126);
	if (flag[0] && flag[1]) //if both flags are 1 (we received >>) we create a file in case it does not exist or open it with append option so we do not overwrite it
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if(flag[0] && !flag[1]) //if we received > we do the same but with trunc option, overwriting it
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flag[0] && oldfd != -1) //if we did not receive > or >> and our oldfd is valid
		fd = open (path,O_RDONLY); //open the fd with read permissions
	else
		fd = oldfd; //otherwise we set fd to our oldfd
	return (fd);
}

/*
 *	This function is used when we get >> in our commands
 */

t_ms	*get_of_concat(t_ms *node, char **args, int *i)
{
	char	*new_line;
	int		flag[2]; //these flags will be used in get_fd function to check the case we have

	flag[0] = 1;
	flag[1] = 1;
	new_line = "minishell: syntax error near unexpected token `newline'"; // we asign our newline so print it in case we have an error
	(*i)++;
	if (args[++(*i)])
		node->outfile = get_fd(node->outfile, args[*i], flag); //we asign our file descriptor to our node outfile
	if (!args[*i] || node->outfile == -1) //if there is no value or we got an error while taking file descriptor value
	{
		*i = -1; //we set i to -1 (error)
		if (node->outfile != -1) // if we got an error taking our file descriptor value
		{
			ft_putendl_fd(new_line, 2); //we print our error message
			g_status = 2; //set our status to 2
		}
		else //if we got our fd properly but dont have an args[*i] value
			g_status = 1; // we set our status to 1
	}
	return (node); //return the node with its new values
}

/*
 * This function is used when we get > in our commands
 */

t_ms	*get_of_redir(t_ms *node, char **args, int *i)
{
	char	*new_line;
	int		flag[2]; //these flags will be used in get_fd function to check the case we have

	flag[0] = 1;
	flag[1] = 0;
	new_line = "minishell: syntax error near unexpected token `newline'"; // we asign our newline so print it in case we have an error
	(*i)++;
	if (args[(*i)])
		node->outfile = get_fd(node->outfile, args[*i], flag); //we asign our file descriptor to our node outfile
	if (!args[*i] || node->outfile == -1) //if there is no value or we got an error while taking file descriptor value
	{
		*i = -1; //we set i to -1 (error)
		if (node->outfile != -1) // if we got an error taking our file descriptor value
		{
			ft_putendl_fd(new_line, 2); //we print our error message
			g_status = 2; //set our status to 2
		}
		else //if we got our fd properly but dont have an args[*i] value
			g_status = 1; // we set our status to 1
	}
	return (node); //return the node with its new values
}

t_ms	*get_inf_redir(t_ms *node, char **args, int *i)
{
	char	*new_line;
	int		flag[2]; //these flags will be used in get_fd function to check the case we have

	flag[0] = 0;
	flag[1] = 0;
	new_line = "minishell: syntax error near unexpected token `newline'"; // we asign our newline so print it in case we have an error
	(*i)++;
	if (args[(*i)])
		node->infile = get_fd(node->infile, args[*i], flag); //we asign our file descriptor to our node outfile
	if (!args[*i] || node->infile == -1) //if there is no value in args[*i] or we got an error while taking fd value
	{
		*i = -1; //we set i to -1 (error)
		if (node->infile != -1) // if we got an error taking our file descriptor value
		{
			ft_putendl_fd(new_line, 2); //we print our error message
			g_status = 2; //set our status to 2
		}
		else //if we got our fd properly but dont have an args[*i] value
			g_status = 1; // we set our status to 1
	}
	return (node); //return the node with its new values
}

t_ms	*get_inf_heredoc(t_ms *node, char **args, int *i)
{
	char	*aux[2];
	char	*new_line;
	char	*str[2];
	

	str[0] = NULL;
	str[1] = NULL;
	aux[0] = NULL;
	aux[1] = "minishell: warning: here-document delimited by end-of-file"; //this will be the message for the here doc once it is open
	new_line = "minishell: syntax error near unexpected token `newline'"; // we asign our newline so print it in case we have an error
	(*i)++;
	if (args[++(*i)])
	{
		aux[0] = args[*i];
		node->infile = get_heredoc(str,aux); // we set the infile to the heredoc which we will create with get_heredoc
	}
	if (!args[*i] || node->infile == -1) // if there is no value in args[*i] or we got an error while taking fd value
	{
		*i = -1; //we set i to -1 (error)
		if (node->infile != -1) // if we got an error taking our fd value
		{
			ft_putendl_fd(new_line, 2); //we print our error message
			g_status = 2; // set our status to 2
		}
	}
	return (node); //we return the node with its new values
}
