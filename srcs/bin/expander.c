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

int	ft_strchr_r(const char *str, char *check)
{
	int	i[2];

	i[0] = -1;
	if (!str)
		return (-1);
	while (str[++i[0]])
	{
		i[1] = -1;
		while (check[++i[1]])
		{
			if (str[i[0]] == check[i[1]])
				return (i[0]);
		}
	}
	return (-1);
}

int	ft_strchr_r_i(const char *str, char *check)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (ft_strchr(check, str[i]))
			return (i);
		i++;
	}
	return (-1);
}

char	*expand_path(char *str, int i, int qte[2], char *value)
{
	char	*path;
	char	*holder;

	qte[0] = 0;
	qte[1] = 0;
	while (str && str[++i])
	{
		qte[0] = (qte[0] + (!qte[1] && str[i] == '\'')) % 2;
		qte[1] = (qte[1] + (!qte[0] && str[i] == '\"')) % 2;
		if (!qte[0] && !qte[1] && str[i] == '~' && \
			(i == 0 || str[i - 1] != '$'))
		{
			holder = ft_substr(str, 0, i);
			path = ft_strjoin(holder, value);
			free (holder);
			holder = ft_substr(str, i + 1, ft_strlen(str));
			free (str);
			str = ft_strjoin(path, holder);
			free (holder);
			free (path);
			return (expand_path(str, i + ft_strlen(value) - 1, qte, value));
		}
	}
	free (value);
	return (str);
}

static char	*get_substr(char *str, int i, t_read *rd)
{
	char	*ret;
	int		pos;
	char	*var;
	char	*holder;

	pos = ft_strchr_r_i(&str[i], "|\"\'$?>< ") + (ft_strchr("$?", str[i]) != 0);
	if (pos == -1)
		pos = ft_strlen(str) - 1;
	ret = ft_substr(str, 0, i - 1);
	var = search_env_len(rd->env, &str[i], pos);
	if (!var[0] && str[i] == '$')
		var = ft_itoa(rd->pid);
	else if (!var[0] && str[i] == '?')
		var = ft_itoa(g_status);
	holder = ft_strjoin(ret, var);
	free (ret);
	ret = ft_strjoin(holder, &(str[i + pos]));
	free (var);
	free (holder);
	free (str);
	return (ret);
}

char	*expand_var(char *str, int qte[2], int i, t_read *rd)
{
	qte[0] = 0;
	qte[1] = 0;
	while (str && str[++i] != '\0')
	{
		qte[0] = (qte[0] + (!qte[1] && str[i] == '\'')) % 2;
		qte[1] = (qte[1] + (!qte[0] && str[i] == '\"')) % 2;
		if (!qte[0] && str[i] == '$' && str[i + 1] && \
		((ft_strchr_r_i(&str[i + 1], " :;/~%^{}") && !qte[1]) || \
			(ft_strchr_r_i(&str[i + 1], "\":;/~%^{}") && qte[1])))
			return (expand_var(get_substr(str, ++i, rd), qte, -1, rd));
	}
	return (str);
}
