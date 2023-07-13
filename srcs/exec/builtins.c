#include "../../includes/minishell.h"

int	exec_builtin(char **args, s_env env)
{
	int result;

	result = 0;
	if (ft_strcmp(args[0], "echo") == 0)
		result = echo(args);
	if (ft_strcmp(args[0], "cd") == 0)
		result = cd(args, env);
	if (ft_strcmp(args[0], "pwd") == 0)
		result = pwd();
	if (ft_strcmp(args[0], "env") == 0)
		print_env(env);
	if (ft_strcmp(args[0], "export") == 0)
		export_env(env, args);
	if (ft_strcmp(args[0], "unset") == 0)
		unset_env(env, args);
	return (result);
}
