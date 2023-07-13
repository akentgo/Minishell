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