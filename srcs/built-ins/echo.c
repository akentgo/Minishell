#include "../../includes/minishell.h"

int	ft_countchar(char *s, char c)
{
	int	ct;
	if (!s)
		return (0);
	ct = 0;
	while (*s)
	{
		if (*s == c)
			ct++;
		s++;
	}
	return (ct);
}

int ms_echo(t_list *cmd)
{
	char	**argv;
	t_ms	*n;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 1;
	n = cmd->content;
	argv = n->cmd;
	while (argv && argv[++i[0]])
	{
		if (!i[1] && !ft_strncmp(argv[i[0]], "-n", 2) && (ft_strlen(argv[i[0]] - 1) == ft_countchar(argv[i[0]], 'n')))
			i[2] = 0;
		else
		{
			i[1] = 1;
			ft_putstr_fd(argv[i[0]], 1);
			if (argv[i[0] + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	if(i[2])
		write(1, "\n", 1);
	return (0);
}
