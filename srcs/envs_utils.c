/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:18:18 by akent-go          #+#    #+#             */
/*   Updated: 2023/08/09 16:56:22 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	unset_helper(t_env *env, char *s)
{
	t_env	*handler;

	while (env->next != NULL)
	{
		if (!ft_strcomp(env->next->name, s))
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
}

/*
 * this function is used to remove an element from the list, it will do
 * the work for unset command (that's why it's unset_env), it shouldn't have
 * any leaks but I haven't tested it
 */
int	ms_unset(t_env *env, char **s, int i)
{
	t_env	*holder;
	t_env	*handler;

	holder = env;
	if (!env)
		return (0);
	while (s && s[++i])
	{
		if (!ft_arealnum(s[i]) && ft_strchr(s[i], '_') == 0)
		{
			ms_error(12, s[i], 127);
			return (1);
		}
		unset_helper(env, s[i]);
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

int	ms_export(t_env *env, char **str, int i)
{
	char	**h;

	if (!str[i + 1])
		return (print_empty_env(env));
	while (str[++i])
	{
		h = ft_split_env(str[i]);
		if (!h || !h[0] || !h[1] || h[2] != NULL)
			return (0);
		if (env_size(h) != 2)
			return (0);
		if (ft_isdigit(h[0][0]) || (!ft_arealnum(h[0]) && \
		!ft_strchr(h[0], '_')))
		{
			ms_error(12, str[i], 127);
			return (1);
		}
		export_helper(env, h);
		ft_free_matrix(&h);
	}
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
