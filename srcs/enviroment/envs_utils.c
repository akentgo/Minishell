#include "../../includes/minishell.h"

extern int	g_status;

/*
 * this function compares 2 strings and returns 0 if they're exactly the same or 
 * other number if they're not
 */
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
	printf("Str->%s\n", str);
	while (env->next != NULL)
	{
		if (!ft_strcomp(env->next->name, str))
		{
			printf("Found you\n");
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

	printf("In export\n");
	holder = ft_split_env(str);
	if (!holder || !holder[0] || !holder[1] || holder[2] != NULL)
		return ;
	printf("Holder0 = %s\n", holder[0]);
	printf("Holder1 = %s\n", holder[1]);
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

char	*env_parser(char *str, char *sep)
{
	char	*new_str;
	int		qte[2];
	int		i;

	qte[0] = 0;
	qte[1] = 0;
	i = 0;
	while (str[i])
	{
		if (ft_strchr(sep, str[i]) && str[i] != '\0')
		{
			new_str = malloc(sizeof(char) * i + 1);
			if (!new_str)
				return (NULL);
			ft_strlcpy(new_str, str, i);
			return (new_str);
		}
		i++;
	}
	return (new_str);
}

void	export_last_cmd(t_env *env, char *s1, char *s2)
{
	while (env->next != 0)
	{
		if (ft_strcomp(env->name, s1))
			{
				ft_strreplace(&(env->value), s2);
				return ;
			}
		env = env->next;
	}
	env->next = new_env();
	env->name = ft_strdup(s1);
	env->value = ft_strdup(s2);
}

