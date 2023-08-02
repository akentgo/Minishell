/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:41:21 by akent-go          #+#    #+#             */
/*   Updated: 2023/07/30 17:41:22 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *	This function will create an element t_ms (type minishell) initializing
 *	every parameter for it
 */

t_ms	*ms_init(void)
{
	t_ms	*ms;

	ms = malloc(sizeof(t_ms));
	if (!ms)
		return (NULL);
	ms->cmd = NULL;
	ms->path = NULL;
	ms->infile = INFILE;
	ms->outfile = OUTFILE;
	return (ms);
}

/*
 *	This function cleans the list, args and tmp, avoiding leaks
 */
t_list	*clear_ms(t_list *cmd, char **args, char **tmp)
{
	ft_lstclear(&cmd, free_cmd);
	ft_free_matrix(&tmp);
	ft_free_matrix(&args);
	return (NULL);
}

/*
 *	This function will trim every element in our arguments, deleting quotes
 */

char	**cmd_trim(char	**args)
{
	char	**tmp;
	char	*aux;
	int		i;
	int		j[2];

	i = -1;
	j[0] = 0;
	j[1] = 0;
	tmp = dup_matrix(args);
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

t_ms	*get_redir(t_ms *node, char **a[2], int *i)
{
	if (a[0][*i])
	{
		if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '>'\
				&& a[0][*i + 2] && (!a[0][*i + 2][0] || a[0][*i + 2][0] != '>'))
			node = get_of_concat(node, a[1], i);
		else if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] != '>')
			node = get_of_redir(node, a[1], i);
		else if (a[0][*i][0] == '<' && a[0][*i + 1] && a[0][*i + 1][0] == '<'\
				&& a[0][*i + 2] && (!a[0][*i + 2][0] || a[0][*i + 2][0] != '<'))
			node = get_inf_heredoc(node, a[1], i);
		else if (a[0][*i][0] == '<' && a[0][*i + 1] && a[0][*i + 1][0] != '<')
			node = get_inf_redir(node, a[1], i);
		else if (a[0][*i][0] != '|' && a[0][*i][0] != '<' && \
					a[0][*i][0] != '>')
			node->cmd = ft_expand_arr(node->cmd, a[1][*i]);
		else
			check_redir_caller(a, i);
		return (node);
	}
	ms_error(REDIRERROR, NULL, 2);
	*i = -2;
	return (node);
}

/*
 *	This function will set the message for errors during redirections >> and << 
 */
void	check_redir_caller(char **a[2], int *i)
{
	if (a[0][*i][0] == '>')
		check_redir_out(a, i);
	else if (a[0][*i][0] == '<')
		check_redir_in(a, i);
}
