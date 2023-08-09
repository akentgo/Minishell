/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:22:27 by akent-go          #+#    #+#             */
/*   Updated: 2023/08/09 16:56:26 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

/*
 * this function creates a new variable with empty values
 */
t_env	*new_env(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = NULL;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

/*
 * this function fills a list with every env variable 
 */
void	env_fill(t_env **list, char **env)
{
	int		i;
	char	**holder;
	t_env	*head;
	t_env	*tmp;

	i = -1;
	*list = new_env();
	tmp = *list;
	while (++i < env_size(env))
	{
		holder = ft_split_env(env[i]);
		tmp->name = ft_strdup(holder[0]);
		tmp->value = ft_strdup(holder[1]);
		tmp->next = new_env();
		ft_free_matrix(&holder);
		tmp = tmp->next;
	}
}

char	*set_var(char *name, char *value)
{
	char	*new;
	char	*aux;

	if (!name || !value)
		return (NULL);
	aux = ft_strjoin(name, "=");
	new = ft_strjoin(aux, value);
	free (aux);
	return (new);
}

/*
 * this is the main function, first allocate memory for the first element
 * create the list starting from it and print every list element as env 
 * command does
 */
t_env	*env_set(char **env)
{
	t_env	*enviro;

	env_fill(&enviro, env);
	return (enviro);
}
