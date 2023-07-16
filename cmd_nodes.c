#include "includes/minishell.h"

/*
 *	This function will create an element t_ms (type minishell) initializing
 *	every parameter for it
 */

static t_ms	*ms_init(void)
{
	t_ms	*mini;

	mini = malloc(sizeof(t_ms));
	if (!mini)
		return (NULL);
	mini->cmd = NULL;
	mini->path = NULL;
	mini->infile = INFILE;
	mini->outfile = OUTFILE;
	return (mini);
}

/*
 *	This function cleans the list, args and tmp, avoiding leaks
 */

static t_list	*clear_ms(t_list *cmd, char **args, char **tmp)
{
	ft_lstclear(&cmd, free_cmd);
	ft_free_matrix(&tmp);
	ft_free_matrix(&args);
	return (NULL);
}

/*
 *	This function will trim every element in our arguments, deleting quotes
 */

static char	**cmd_trim(char	**args)
{
	char	**tmp;
	char	*aux;
	int		i;
	int		j[2];

	i = -1;
	j[0] = 0;
	j[1] = 0;
	tmp = dup_matrix(args); //create a duplicate to avoid editing the original
	while (tmp && tmp[++i])
	{
		aux = ft_trim(tmp[i], j);
		free (tmp[i]);
		tmp[i] = aux;
	}
	return (tmp);
}

/*
 * This function will get the params, parsing our outfile, infile and pipes
 */

static t_ms	*get_redir(t_ms *node, char **a[2], int *i)
{
	if (a[0][*i]) //if there is a command
	{
		if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '>'\
				&& a[0][*i + 2] && (!a[0][*i + 2][0] || a[0][*i + 2][0] != '>')) //if we have ">>" we must append to or create our outfile (functions in get_files.c)
			node = get_of_concat(node, a[1], i);
		else if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] != '>') // if we have ">" (and do not have ">>" since the last condition is false we just redirect our output to an outfile
			node = get_of_redir(node, a[1], i);
		else if (a[0][*i][0] == '<' && a[0][*i + 1] && a[0][*i + 1][0] == '<'\
				&& a[0][*i + 2] && (!a[0][*i + 2][0] || a[0][*i + 2][0] != '<')) // if we have "<<" we start a heredoc
			node = get_inf_heredoc(node, a[1], i);
		else if (a[0][*i][0] == '<' && a[0][*i + 1] && a[0][*i + 1][0] != '<') // if we have '<' we assign our infile
			node = get_inf_redir(node, a[1], i);
		else if (a[0][*i][0] != '|' && a[0][*i][0] != '<' && \
					a[0][*i][0] != '>') //if we do not have a pipe
			node->cmd = ft_expand_arr(node->cmd, a[1][*i]);
		else
			check_redir_caller(a, i);
		return (node);
	}
	//ms_error(REDIRERROR, NULL, 2);
	*i = -2;
	return (node);
}

/*
 *	This function will set the message for errors during redirections >> and << 
 */

void	check_redir_caller(char **a[2], int *i)
{
	printf("llegamos al caller\n");
	if (a[0][*i][0] == '>')
		check_redir_out(a, i);
	else if (a[0][*i][0] == '<')
		check_redir_in(a, i);
}

/*
 *	This function will check for errors when more than 3 '<' symbols are found
 */
void	check_redir_in(char **a[2], int *i)
{
	int	n[2]; //2 counters
	char	*new_line; //error line

	new_line = ft_strdup("syntax error near unexpected token `"); //set the frist part of the error message
	n[0] = 0;
	n[1] = 0;
	while (a[0][*i + n[0]] && a[0][*i + n[0]][0] == '<' && n[0] < 3) //increase our counter n[0] to 3 as far as we find '<'
		n[0]++;
	n[1] = n[0]; //set n[1] to n[0] value
	while (a[0][*i + n[1]] && a[0][*i + n[1]][0] == '<' && n[1] < 6) //from 3 to 6 we increase our counter if we find more '<'
		n[1]++;
	if (n[1] <= 3) //if n[1] is 3 it means we found <<< so we set the error message
		new_line = ft_strjoin(new_line, "newline'");
	else //if n is different from 3 (which means it is higher
	{
		n[1] -= 3; //substract 3 from n[1] so we skip the 3 first '<'
		while (n[1]-- > 0) //for each '<' found we add one to our error message
			new_line = ft_strjoin(new_line, "<");
		new_line = ft_strjoin(new_line, "'"); //add the last character to our error message
	}
	ft_putendl_fd(new_line, 2); //print the message
	free (new_line); //free the malloc
	*i = -2; //set i to -2 (error)
}

/*
 * This function works as check_redir_in but when we count '>' we only count 2 max before the error, instead of 3
 */
void	check_redir_out(char **a[2], int *i)
{
	int	n[2];
	char	*new_line;

	new_line = ft_strdup("syntax error near unexpected token `");
	n[0] = 0;
	n[1] = 0;
	while (a[0][*i + n[0]] && a[0][*i + n[0]][0] == '>' && n[0] < 2)
		n[0]++;
	n[1] = n[0];
	while (a[0][*i + n[1]] && a[0][*i + n[1]][0] == '>' && n[1] < 4)
		n[1]++;
	if (n[1] <= 2)
		new_line = ft_strjoin(new_line, "newline'");
	else
	{
		n[1] -= 2;
		while (n[1]-- > 0)
			new_line = ft_strjoin(new_line, ">");
		new_line = ft_strjoin(new_line, "'");
	}
	ft_putendl_fd(new_line, 2);
	free (new_line);
	*i = -2;
}

/*
 * This function will fill our list of t_ms variables
 */
		//printf("en ms_fill -> %s\n", args[i]);

t_list	*ms_fill(char **args, int i)
{
	t_list	*cmd[2]; //this will hold our list of cmds
	char	**tmp[2]; //this will be a temporal variable which will work as a holder

	cmd[0] = NULL;
	tmp[1] = cmd_trim(args); //we hold our arguments trimmed in tmp[1] args lo guarda bien
	while (args[++i]) //for each string
	{
		cmd[1] = ft_lstlast(cmd[0]); //we set cmd[1] as the last element of the list (NULL at the beginning)
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0])) //if we are at the first position or, we are in a pipe followed by something
		{
			i += args[i][0] == '|'; //we increase our counter if we are in a pipe
			ft_lstadd_back(&cmd[0], ft_lstnew(ms_init())); //we add a new element at cmd[0] list
			cmd[1] = ft_lstlast(cmd[0]); //we set cmd[1] to the last element of the cmd[0] list again
		}
		tmp[0] = args; //we set tmp[0] to our arguments again
		cmd[1]->content = get_redir(cmd[1]->content, tmp, &i); // we set our content to the result of our get_redir function
		if (i < 0) //if i has -1 value means taht something went wrong so we free everything and return
			return (clear_ms(cmd[0], args, tmp[1]));
		if (!args[i]) //if there is not an args[i] we just break our loop
			break ;
	} 
	ft_free_matrix(&tmp[1]); // free our matrix tmp[1]
 	ft_free_matrix(&args); //free our matrix args */
	return (cmd[0]); //return our cmd list
}
/*
	Esta función nos crea una copia de el primer argumento y al final de esta, nos añade el segundo argumento
*/
char	**ft_expand_arr(char **in, char *new)
{
	char	**ret;
	int		wrds;
	int		i;

	i = -1;
	ret = NULL;
	if (!new)
		return (in);
	wrds = ft_matrixlen(in); //nos guarda el numero de palabras
	ret = malloc(sizeof(char *) * (wrds + 2)); //hacemos un malloc para la copia + (el string a añadir al final y el nulo)
	if (!ret)
		return (in);
	ret[wrds + 1] = NULL;
	while (++i < wrds)
	{
		ret[i] = ft_strdup(in[i]);
		if (!ret[i])
		{
			ft_free_matrix(&in);
			ft_free_matrix(&ret);
		}
	}
	ret[i] = ft_strdup(new);
	ft_free_matrix(&in);
	return (ret);
}
