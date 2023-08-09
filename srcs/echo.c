/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:15:47 by akent-go          #+#    #+#             */
/*   Updated: 2023/08/09 16:56:12 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ms_echo(t_list *cmd)
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
		if (!i[1] && !ft_strncmp(argv[i[0]], "-n", 2))
			i[2] = 0;
		else
		{
			i[1] = 1;
			ft_putstr_fd(argv[i[0]], 1);
			if (argv[i[0] + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	if (i[2])
		write(1, "\n", 1);
	return (0);
}
