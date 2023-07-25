#include "../../includes/minishell.h"

//ya tenemos la funcion pwd

#include <unistd.h>
#include <stdio.h>
#include <limits.h>

int	ms_pwd(void)
{
	char cwd[PATH_MAX];
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		return (SUCCESS);
	}
	else
		return (FAILURE);
}