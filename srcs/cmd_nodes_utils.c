/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nodes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:39:56 by akent-go          #+#    #+#             */
/*   Updated: 2023/07/30 17:45:59 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	check_redir_in(char **a[2], int *i)
{
	int		n[2];
	char	*new_line;

	new_line = ft_strdup("syntax error near unexpected token `");
	n[0] = 0;
	n[1] = 0;
	while (a[0][*i + n[0]] && a[0][*i + n[0]][0] == '<' && n[0] < 3)
		n[0]++;
	n[1] = n[0];
	while (a[0][*i + n[1]] && a[0][*i + n[1]][0] == '<' && n[1] < 6)
		n[1]++;
	if (n[1] <= 3)
		new_line = ft_strjoin(new_line, "newline'");
	else
	{
		n[1] -= 3;
		while (n[1]-- > 0)
			new_line = ft_strjoin(new_line, "<");
		new_line = ft_strjoin(new_line, "'");
	}
	ft_putendl_fd(new_line, 2);
	free (new_line);
	*i = -2;
}

/*
 * This function works as check_redir_in but when we count '>' 
 	we only count 2 max before the error, instead of 3
 */
void	check_redir_out(char **a[2], int *i)
{
	int		n[2];
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

t_list	*ms_fill(char **args, int i)
{
	t_list	*cmd[2];
	char	**tmp[2];

	cmd[0] = NULL;
	tmp[1] = cmd_trim(args);
	while (args[++i])
	{
		cmd[1] = ft_lstlast(cmd[0]);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			i += args[i][0] == '|';
			ft_lstadd_back(&cmd[0], ft_lstnew(ms_init()));
			cmd[1] = ft_lstlast(cmd[0]);
		}
		tmp[0] = args;
		cmd[1]->content = get_redir(cmd[1]->content, tmp, &i);
		if (i < 0)
			return (clear_ms(cmd[0], args, tmp[1]));
		if (!args[i])
			break ;
	}
	ft_free_matrix(&tmp[1]);
	ft_free_matrix(&args);
	return (cmd[0]);
}
/*
	Esta función nos crea una copia de el primer argumento y al final de esta,
	nos añade el segundo argumento
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
	wrds = ft_matrixlen(in);
	ret = malloc(sizeof(char *) * (wrds + 2));
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
