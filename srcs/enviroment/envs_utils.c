/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:18:18 by akent-go          #+#    #+#             */
/*   Updated: 2023/07/30 17:18:43 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

/*
 * this function returns the number of env variables existing
 */
int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/*
 * this function is used to remove an element from the list, it will do
 * the work for unset command (that's why it's unset_env), it shouldn't have
 * any leaks but I haven't tested it
 */
int	ms_unset(t_env *env, char *str)
{
	t_env	*holder;
	t_env	*handler;

	holder = env;
	if (!env)
		return (0);
	if (!ft_arealnum(str) && ft_strchr(str, '_') == 0)
	{
		ms_error(12, str, 127);
		return (1);
	}
	while (env->next != NULL)
	{
		if (!ft_strcomp(env->next->name, str))
		{
			free(env->next->name);
			free(env->next->value);
			handler = env->next;
			env->next = env->next->next;
			free (handler);
		}
		else
			env = env->next;
	}
	return (0);
}

void	export_helper(t_env *env, char **holder)
{
	while (env->next)
	{
		if (!ft_strcomp(env->name, holder[0]))
		{
			ft_strreplace(&(env->value), holder[1]);
			return ;
		}
		env = env->next;
	} 
	env->next = new_env();
	env->name = ft_strdup(holder[0]);
	env->value = ft_strdup(holder[1]);
}

int	ms_export(t_env *env, char *str, int i)
{
	char	**h;

	if (!str)
		return (0);
	h = ft_split_env(str); //esto hay que liberarlo en algún momento
	if (!h || !h[0] || !h[1] || h[2] != NULL)
		return (0);
	if (env_size(h) != 2)
		return (0);
	if (ft_isdigit(h[0][0]) || (!ft_arealnum(h[0]) && !ft_strchr(h[0], '_')))
	{
		ms_error(12, str, 127);
		return (1);
	}
	export_helper(env, h);
	return (0);
}

/*
 *	This function will print each environment variable
 */

void	print_env(t_env *env)
{
	if (!env)
		return ;
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
