/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:59:51 by akent-go          #+#    #+#             */
/*   Updated: 2023/08/09 17:03:58 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	ft_strchr_r(const char *s, char *check)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (ft_strchr(check, s[i]))
			return (i);
		i++;
	}
	return (-1);
}

char	*expand_path(char *s, int i, int qte[2], char *value)
{
	char	*path;
	char	*holder;

	qte[0] = 0;
	qte[1] = 0;
	while (s && s[++i])
	{
		qte[0] = (qte[0] + (!qte[1] && s[i] == '\'')) % 2;
		qte[1] = (qte[1] + (!qte[0] && s[i] == '\"')) % 2;
		if (!qte[0] && !qte[1] && s[i] == '~' && \
			(i == 0 || s[i - 1] != '$'))
		{
			holder = ft_substr(s, 0, i);
			path = ft_strjoin(holder, value);
			free (holder);
			holder = ft_substr(s, i + 1, ft_strlen(s));
			free (s);
			s = ft_strjoin(path, holder);
			free (holder);
			free (path);
			return (expand_path(s, i + ft_strlen(value) - 1, qte, value));
		}
	}
	free (value);
	return (s);
}

static char	*get_substr(char *s, int i, t_read *p)
{
	char	*ret;
	int		pos;
	char	*var;
	char	*holder;

	pos = ft_strchr_r(&s[i], "|\"\'$?>< ") + (ft_strchr("$?", s[i]) != 0);
	if (pos == -1)
		pos = ft_strlen(s) - 1;
	ret = ft_substr(s, 0, i - 1);
	var = search_env_len(p->env, &s[i], pos);
	if (!var[0] && s[i] == '$')
		var = ft_itoa(p->pid);
	else if (!var[0] && s[i] == '?')
		var = ft_itoa(g_status);
	holder = ft_strjoin(ret, var);
	free (ret);
	ret = ft_strjoin(holder, &(s[i + pos]));
	free (var);
	free (holder);
	free (s);
	return (ret);
}

char	*expand_var(char *s, int qte[2], int i, t_read *p)
{
	qte[0] = 0;
	qte[1] = 0;
	while (s && s[++i] != '\0')
	{
		qte[0] = (qte[0] + (!qte[1] && s[i] == '\'')) % 2;
		qte[1] = (qte[1] + (!qte[0] && s[i] == '\"')) % 2;
		if (!qte[0] && s[i] == '$' && s[i + 1] && \
		((ft_strchr_r(&s[i + 1], " :;/~%^{}") && !qte[1]) || \
			(ft_strchr_r(&s[i + 1], "\":;/~%^{}") && qte[1])))
			return (expand_var(get_substr(s, ++i, p), qte, -1, p));
	}
	return (s);
}
