#include "../../includes/minishell.h"

extern int	g_status;

void    ft_free_env(t_env *env) //ESTO HAY QUE ARREGLARLO, NO DEBERÍA FUNCIONAR Y CREO QUE NI SE USA
{
    if (env->next)
        ft_free_env(env->next);
    free(env->name);
    free(env->value);
    free(env);
}

char    **ft_split_env(char *str)
{
    int     i;
    char    **split;

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

void	print_empty_env(t_env *env)
{
	if (!env)
		return ;
	while (env->next)
	{
		printf("declare -x %s=%s\n", env->name, env->value);
		env = env->next;
	}
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