#include "includes/minishell.h"

extern int	g_status;

/*
 *	This function create a single matrix from two
 */
char **ft_matrix_append(char ***big, char **small, int n)
{
	char **aux;
	int i[3];

	i[0] = -1; //this is the big matrix counter
	i[1] = -1; //this is the small matrix counter
	i[2] = -1; //this is the new matrix counter
	if (!big || !*big || n < 0 || n >= ft_matrixlen(*big))
		return (NULL);
	aux = malloc(sizeof(char *) * (ft_matrixlen(*big) + ft_matrixlen(small) + 1));
	if (!aux)
		return (NULL);
	while ((*big)[++i[0]]) //if aux has been created properly and big has content in it
	{
		if (i[0] != n)
			aux[++i[2]] = ft_strdup((*big)[i[0]]);
		else //once we reach n with our big counter
		{
			while (small && small[++i[1]])
				aux[++i[2]] = ft_strdup(small[i[1]]);
		}
	}
	aux[++i[2]] = NULL;
	ft_free_matrix(big);
	*big = aux; //set the pointer to the new matrix
	return (*big); //return the matrix
}
static char	**split_all(char **args, t_read *r)
{
	char	**splitted;
	int		i;
	int		q[2];

	i = -1;
	while (args && args[++i])
	{
		args[i] = expand_var(args[i], q, -1, r);
		args[i] = expand_path(args[i], -1, q, search_env(r->env, "HOME"));
		splitted = redir_split(args[i], "><|");
		ft_matrix_append(&args, splitted, i);
		i += ft_matrixlen(splitted) - 1; //increase the length for i
		ft_free_matrix(&splitted); //free the split to avoid leaks
	}
	return (args);
}

static void	*parse_args(char **args, t_read *p)
{
	int	ex;
	int	i;

	ex = 0;
	p->cmd = ms_fill(split_all(args, p), -1);//fill cmd double array with the arguments find this function in cmd_nodes
	if (!p->cmd) //if it is null return null
		return (p);
	i = ft_lstsize(p->cmd); //save the list length
	//Aqui comprobamos que nos ha guardado el comando bien
	printf("I es = %i\n", i);
	while(p->cmd)
	{
		printf ("El comando es: %s\n", p->cmd->content);
		p->cmd = p->cmd->next;
	}
	/*g_status = builtin(p, p->cmd, &ex, 0); //check builtin function in builtins.c
	while (i-- > 0) //while there is an element in the list
		waitpid(-1, &g_status, 0); //wait for any child process whose process group id is equal to 1 (absolute value of the first parameter)
	if (!ex && g_status == 13) //if is_exit is 0 and the global status is 13 set it to 0
		g_status = 0;
	if (g_status > 255) //if the g_status is greater than 255 divide it by 255
		g_status /= 255;
	if (args && ex) //if we get arguments and ex is not 0 clear the list
	{
		ft_lstclear(&p->cmd, free_cmd); //free_cmd is in error.c
		return (NULL);
	}
	return (p);*/
	return (NULL);
}

void	*check_args(char *out, t_read *p)
{
	char	**a;
	t_ms	*n;

	if (!out)	//if there is an error while getting the prompt just exit
	{
		printf("exit\n");
		return (NULL);
	}
	if (out[0] != '\0') //if out is not empty add it to the history
		add_history(out);
	a = ft_cmdsplit(out, " "); //split our strings by spaces (function in lexer)
	free (out); //free out since we will use 'a' now
	if (!a) //if a does no exist return an error message
		ms_error(QUOTE, NULL, 1);
	if (!a)	//if a does not exist return an empty line
		return ("");
	//hasta aqui funciona
	p = parse_args(a, p);
	/*if (p && p->cmd) //if p exists and p->cmd has been filled properly set n to p->cmd->content
		n = p->cmd->content;
	if (p && p->cmd && n && n->cmd && ft_lstlen(p->cmd) == 1) // if n and p exist and cmd has a length of 1 we save the last command executed in env variable
		export_last_cmd(p->env, "_", n->cmd[ft_matrixlen(n->cmd) - 1]); //export_last_cmd is in envs_utils.c
	if (p && p->cmd)
		ft_lstclear(&p->cmd, free_cmd); //clear p->cmd to avoid leaks, free_cmd is in error.c
	return (p);*/
	return (NULL);
}
