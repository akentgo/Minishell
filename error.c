#include "includes/minishell.h"

extern int	g_status;

/*
 *	This function prints the error message
 */
void	*ms_error(int err_code, char *param, int err)
{
	g_status = err;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(param, 2);
	if (err_code == QUOTE)
		ft_putendl_fd("error while looking for matching quote\n", 2);
	else if (err_code == NODIR)
		ft_putendl_fd(": no such file or directoy:", 2);
	else if (err_code == NOPERM)
		ft_putendl_fd("permission denied:", 2);
	else if (err_code == NCMD)
		ft_putendl_fd("command not found:", 2);
	else if (err_code == DUPERROR)
		ft_putendl_fd("dup2 failed", 2);
	else if (err_code == FORKERROR)
		ft_putendl_fd("fork failed\n", 2);
	else if (err_code == PIPERROR)
		ft_putendl_fd("error creating pipe\n", 2);
	else if (err_code == PIPENDERROR)
		ft_putendl_fd("syntax error near unexpected token `|'\n", 2);
	else if (err_code == MEM)
		ft_putendl_fd("not memory left on device\n", 2);
	else if (err_code == IS_DIR)
		ft_putendl_fd(": Is a directory:", 2);
	else if (err_code == NOT_DIR)
		ft_putendl_fd(": Not a directory:", 2);
	return (0);
}

/*int	ms_exit(t_list *cmd, int *ex)
{
	t_ms	*node;
	long	status[2];

	node = cmd->content; //assign to node the content of cmd
	*ex = !cmd->next; //assign 0 to ex if there is no next to cmd, or next directin if there is next
	if (*ex) // if ex is not 0 print exit message
		ft_putstr_fd("exit\n", 2);
	if (!node->cmd || !node->cmd[1]) //if the command list in node is empty or its the first command is empty return 0
		return (0);
	status[1] = ft_atoi_ //////////////////////

}*/

/*
 *	This function will check for errors during cd execution
 */
void	cd_error(char **str[2]) //str[0] is the full command, str[1] is 
{
	DIR	*dir;

	dir = NULL;
	if (str[0][1]) //if str[0] has an argument open it and save it in 'dir'
		dir = opendir(str[0][1]);
	if (!str[0][1] && str[1][0] && !str[1][0][0]) //if str[0] has no arguments, str[1] is not empty but its first char is empty send error msg
	{
		g_status = 1;
		ft_putstr_fd("minishell: HOME not set\n", 2);
	}
	if (str[1][0] && !str[0][1]) //if str[1] is not empty and str[0] has no arguments we set the status to 1 if opening str[1] returns an error
		g_status = chdir(str[1][0]) == -1;
	if (str[0][1] && dir && access(str[0][1], F_OK) != -1) //if s[0] has an argument and dir exists and str[0] argument exists do chdir to that folder
		chdir(str[0][1]);
	else if (str[0][1] && access(str[0][1], F_OK) == -1) //if str[0] has an argument but it is no accessible call to error function
		ms_error(NODIR, str[0][1], 1);
	else if (str[0][1]) // if str[0] has an argument and reaches here it means it is not a directory so call to error function
		ms_error(NOT_DIR, str[0][1], 1);
	if (str[0][1] && dir) //if str[0] has an argument and dir exists, close dir
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

void	ft_free_matrix(char ***matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[0] && matrix[0][i])
	{
		free (matrix[0][i]);
		i++;
	}
	if (matrix)
	{
		free (matrix[0]);
		*matrix = NULL;
	}
}

int	ft_matrixlen(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return (0);
	while (matrix[i])
		i++;
	return (i);
}
char	**dup_matrix(char **matrix)
{
	char	**new_matrix;
	int		i;

	i = -1;
	new_matrix = malloc(sizeof (char *) * (ft_matrixlen(matrix) + 1));
	if (!new_matrix)
		return (NULL);
	while (matrix[++i])
		new_matrix[i] = ft_strdup(matrix[i]);
	new_matrix[i] = NULL;
	return (new_matrix);
}

