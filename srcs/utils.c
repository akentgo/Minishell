/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:16:20 by akent-go          #+#    #+#             */
/*   Updated: 2023/07/30 18:33:04 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**turn_into_arr(t_env *envs)
{
	int		word_ct;
	char	**res;
	char	*temp;
	int		size;

	size = 0;
	word_ct = 0;
	while (envs->next)
	{
		size++;
		envs = envs->next;
	}
	res = malloc(sizeof(char *) * size);
	while (envs->next)
	{
		temp = ft_strjoin(envs->name, "=");
		res[word_ct] = ft_strjoin(temp, envs->value);
		free(temp);
		word_ct++;
		envs = envs->next;
	}
	return (res);
}

void	ft_strreplace(char **s1, char *s2)
{
	char	*sdup;

	sdup = ft_strdup(s2);
	*s1 = sdup;
	return ;
}

int	ft_strcomp(char *a, char *b)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (!a || !b)
		return (1);
	if (ft_strlen(a) != ft_strlen(b))
		return (1);
	while (a[i] && b[i] && (a[i] != '\0' && b[i] != '\0') && n == 0)
	{
		n = a[i] - b[i];
		i++;
	}
	return (n);
}

int	ft_arealnum(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (ft_isalnum(str[i]))
			return (1);
	}
	return (0);
}
