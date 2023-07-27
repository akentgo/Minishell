#include "includes/minishell.h"

void    sg_handle(int sig)
{
    rl_on_new_line();
    rl_redisplay();
    rl_replace_line("", 0);
    printf("\033[K\n");
    rl_on_new_line();
    rl_redisplay();
}