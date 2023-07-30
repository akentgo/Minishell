#include "../includes/minishell.h"

extern int	g_status;

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
	else if (err_code == PIPENDERROR)
		ft_putstr_fd("El Nano🇪🇸 : syntax error near unexpected token `|'\n", 2);
	else if (err_code == MEM)
		ft_putstr_fd("El Nano🇪🇸 : not memory left on device\n", 2);
	else if (err_code == IS_DIR)
		ft_putstr_fd("El Nano🇪🇸 : Is a directory: ", 2);
	else if (err_code == NOT_DIR)
		ft_putstr_fd("El Nano🇪🇸 : Not a directory: ", 2);
	else if (err_code == 12)
		ft_putstr_fd("El Nano🇪🇸 : Not a valid identifier: ", 2);
	ft_putendl_fd(param, 2);
	return (0);
}

int	ft_atoi_mod(const char *str, long *l)
{
	int	sign;
	
	sign = 1;
	*l = 0;
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '-')
		sign = -sign;
	if (*str == '-' || *str == '+')
		str++;
	if (!ft_isdigit(*str))
		return (-1);
	while (ft_isdigit(*str))
	{
		*l = 10 * *l + (*str - '0');
		str++;
	}
	if (*str && (*str != ' ' && *str != '\t'))
		return (-1);
	*l *= sign;
	return (0);
}

int	ms_exit(t_list *cmd, int *ex)
{
	t_ms	*n;
	long	status[2];

	n = cmd->content; //assign to node the content of cmd
	*ex = !cmd->next; //assign 1 to ex if there is no next to cmd, or 0 if there is next
	if (*ex) // if ex is not 0 print exit message
		ft_putstr_fd("exit\n", 2);
	if (!n->cmd || !n->cmd[1]) //if the command list in node is empty or its the first command is empty return 0
		return (0);
	status[1] = ft_atoi_mod(n->cmd[1], &status[0]); // store 0 or -1 depending on te atoi of cmd[1] (the argument for exit)
	if (status[1] == -1) //if we had a -1 it means we cannot do an atoi to cmd[1] so error message
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(n->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	else if (n->cmd[2]) // if we have more than one arguments error
	{
		*ex = 0;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	status[0] %= 256 + 256 * (status[0] < 0); // do the module of status[0] (the atoi of cmd received) and 256 plus 256 if status is less than 0
	return (status[0]);
	

}

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

