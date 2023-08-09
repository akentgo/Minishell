/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 10:17:47 by asolano-          #+#    #+#             */
/*   Updated: 2023/08/09 17:04:45 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	ms_export1(t_env *env, char *str)
{
	char	**h;

	if (str)
	{
		h = ft_split_env(str);
		if (!h || !h[0] || !h[1] || h[2] != NULL)
			return (0);
		if (env_size(h) != 2)
			return (0);
		if (ft_isdigit(h[0][0]) || (!ft_arealnum(h[0]) && \
		!ft_strchr(h[0], '_')))
		{
			ms_error(12, str, 127);
			return (1);
		}
		export_helper(env, h);
		ft_free_matrix(&h);
	}
	free (str);
	return (0);
}

void	print_var(t_env *env, char *str)
{
	if (!str)
		return ;
	printf("%s\n", search_env(env, str));
}
