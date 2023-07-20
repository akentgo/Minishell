#include "../../includes/minishell.h"

extern int	g_status;

void    ft_free_env(t_env *env)
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