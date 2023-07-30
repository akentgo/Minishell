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
	if (ft_strchr(str, '=') != 0)
		ms_error(12, str, 127);
	while (env->next != NULL)
	{
		if (!ft_strcomp(env->next->name, str))
		{
			free(env->next->name);
			free(env->next->value);
			handler = env->next;
			env->next = env->next->next;
			free (handler);
			return (0);
		}
		else
			env = env->next;
	}
	return (0);
}

/*
 *	This function will set the new env variable or replace its old value if it already existed
 */
void	ms_export(t_env *env, char *str, int i)
{
	char	**holder;

	if (!str)
		return ;
	holder = ft_split_env(str);
	if (str[0] >= '0' && str[0] <= '9')
		ms_error(12, str, 127);
	if (!holder || !holder[0] || !holder[1] || holder[2] != NULL)
		return ;
	while (holder[i] != NULL)
		i++;
	if (i != 2)
		return ;
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

/*
 *	
 */

void	print_var(t_env *env, char *str)
{
	if (!str)
		return ;
	printf("%s\n", search_env(env, str));
}