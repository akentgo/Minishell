/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:26:21 by akent-go          #+#    #+#             */
/*   Updated: 2023/08/09 17:04:40 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

void	ft_free_env(t_env *env)
{
	if (env->next)
		ft_free_env(env->next);
	free(env->name);
	free(env->value);
	free(env);
}

char	**ft_split_env(char *str)
{
	int		i;
	char	**split;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (ft_strlen(str) == i)
		return (NULL);
	split = malloc (sizeof (char *) * 3);
	split[0] = ft_substr(str, 0, i);
	split[1] = ft_substr(str, i + 1, ft_strlen(str));
	split[2] = NULL;
	return (split);
}

int	print_empty_env(t_env *env)
{
	if (!env)
		return (0);
	while (env->next)
	{
		printf("declare -x %s=\"%s\"\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}

/*
 *	This function will print each environment variable
 */

void	print_env(t_env *env, char *cmd)
{
	if (!env)
		return ;
	ms_export1(env, set_var("_", cmd));
	while (env->next)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

void	print_var(t_env *env, char *str)
{
	if (!str)
		return ;
	printf("%s\n", search_env(env, str));
}
