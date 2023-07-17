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