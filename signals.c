#include "includes/minishell.h"

void    sg_handle(int signal)
{
    if (signal == SIGINT)
    {
        ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
    }
}