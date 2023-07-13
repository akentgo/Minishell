#include "../../includes/minishell.h"

extern int	g_status;

/*
 * this function take the env structure and turn it into a char ** so it can be
 * used in execv command
 */
char	**env_to_str(t_env *env)
{
	char	**new_env;
	t_env	*holder;
	int		i;

	holder = env;
	i = 0;
	while (env->next)
	{
		i++;
		env = env->next;
	}
	new_env = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (holder->next)
	{
		new_env[i] = ft_strjoin(holder->name, "=");
		new_env[i] = ft_strjoin(new_env[i], holder->value);
		i++;
		holder = holder->next;
	}
	return (new_env);
}

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
		holder = ft_split(env[i], '=');
		tmp->name = ft_strdup(holder[0]);
		tmp->value = ft_strdup(holder[1]);
		tmp->next = new_env();
	//	printf("%s %s\n", list->name, list->value);
		tmp = tmp->next;
	}
	//printf("Numero de i's->%i\n", i);
}

/*
 * this is the main function, first allocate memory for the first element
 * create the list starting from it and print every list element as env 
 * command does
 */
t_env	*env_set(char **env)
{
	t_env	*enviro;

	//enviro = malloc (sizeof(t_env));
	if (!enviro)
		return (0);
	env_fill(&enviro, env);
	return (enviro);
}
