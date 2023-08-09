/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:19:16 by akent-go          #+#    #+#             */
/*   Updated: 2023/08/09 16:56:20 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	ft_strchr_i(const char *s, int c)
{
	unsigned char	u_char;
	int				i;

	i = 0;
	if (!s)
		return (-1);
	u_char = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == u_char)
			return (i);
		i++;
	}
	if (u_char == '\0')
		return (i);
	return (-1);
}

char	*search_env(t_env *env, char *var)
{
	char	*holder;

	if (var && var[0] == '\0')
		return (ft_strdup(""));
	while (env && env->name)
	{
		if (ft_strncmp(env->name, var, ft_strlen(env->name)) == 0)
		{
			holder = ft_strdup(env->value);
			return (holder);
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*search_env_len(t_env *env, char *var, int n)
{
	char	*holder;

	if (var && var[0] == '\0' || n == 0)
		return (ft_strdup(""));
	while (env && env->name)
	{
		if (ft_strncmp(env->name, var, n) == 0 && ft_strlen(env->name) == n)
		{
			holder = ft_strdup(env->value);
			return (holder);
		}
		env = env->next;
	}
	return (ft_strdup(""));
}
