#include "includes/minishell.h"

char    **turn_into_arr(t_env *envs)
{
    int     word_ct;
    char    **res;
    char    *temp;
    int     size;

    size = 0;
    word_ct = 0;
    while (envs->next)
    {
        size++;
        envs = envs->next;
    }
    res = malloc(sizeof(char *) * size);
    while (envs->next)
    {
        temp = ft_strjoin(envs->name, "=");
        res[word_ct] = ft_strjoin(temp, envs->value);
        free(temp);
        word_ct++;
        envs = envs->next;
    }
    return (res);
}