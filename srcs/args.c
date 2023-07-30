/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:34:49 by akent-go          #+#    #+#             */
/*   Updated: 2023/07/30 17:35:31 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

char	**ft_matrix_append(char ***big, char **sm, int n)
{
	char	**aux;
	int		i[3];

	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	if (!big || !*big || n < 0 || n >= ft_matrixlen(*big))
		return (NULL);
	aux = malloc(sizeof(char *) * (ft_matrixlen(*big) + ft_matrixlen(sm) + 1));
	if (!aux)
		return (NULL);
	while ((*big)[++i[0]])
	{
		if (i[0] != n)
			aux[++i[2]] = ft_strdup((*big)[i[0]]);
		else
		{
			while (sm && sm[++i[1]])
				aux[++i[2]] = ft_strdup(sm[i[1]]);
		}
	}
	aux[++i[2]] = NULL;
	ft_free_matrix(big);
	*big = aux;
	return (*big);
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
		i += ft_matrixlen(splitted) - 1;
		ft_free_matrix(&splitted);
	}
	return (args);
}

static void	*parse_args(char **args, t_read *p)
{
	int	ex;
	int	i;

	ex = 0;
	p->cmd = ms_fill(split_all(args, p), -1);
	if (!p->cmd)
		return (p);
	i = ft_lstsize(p->cmd);
	g_status = builtin(p, p->cmd, &ex, 0);
	while (i-- > 0)
		waitpid(-1, &g_status, 0);
	if (!ex && g_status == 13)
		g_status = 0;
	if (g_status > 255)
		g_status /= 255;
	if (args && ex)
	{
		ft_lstclear(&p->cmd, free_cmd);
		return (NULL);
	}
	return (p);
}

void	*check_args(char *out, t_read *p)
{
	char	**a;
	t_ms	*n;

	if (!out)
	{
		printf("exit\n");
		return (NULL);
	}
	if (out[0] != '\0')
		add_history(out);
	a = ft_cmdsplit(out, " ");
	free (out);
	if (!a)
		ms_error(QUOTE, NULL, 1);
	if (!a)
		return ("");
	p = parse_args(a, p);
	if (p && p->cmd)
		n = p->cmd->content;
	if (p && p->cmd && n && n->cmd && ft_lstsize(p->cmd) == 1)
		export_last_cmd(p->env, "_", n->cmd[ft_matrixlen(n->cmd) - 1]);
	if (p && p->cmd)
		ft_lstclear(&p->cmd, free_cmd);
	return (p);
}
