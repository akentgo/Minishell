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

void    print_all_envs(t_env *env)
{
    while (env->next)
    {
        printf("declare -x %s=%s", env->name, env->value);
        env = env->next;
    }
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
    i--;
    split = malloc (sizeof (char *) * 3);
    split[0] = malloc (sizeof (char) * i + 1);
    ft_strlcpy(split[0], str, i);
    split[0][i] = '\0';
    split[1] = malloc (sizeof (char) * ft_strlen(&str[i + 1]) + 1);
    ft_strlcpy(split[1], str, ft_strlen(&str[i + 1]));
    split[1][i] = '\0';
    split[2] = NULL;
    return (split);
}