#include "includes/minishell.h"

void    sg_handle(int sig)
{
    rl_on_new_line();
    rl_redisplay();
    printf("\b\033[K\n");
    rl_on_new_line();
    rl_redisplay();
}