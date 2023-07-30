/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:12:07 by akent-go          #+#    #+#             */
/*   Updated: 2023/07/30 18:12:07 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status = 0;

/*void	ft_leaks(void)
{
	system("leaks -q minishell");
}*/

static void	ms_getpid(t_read *prompt)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ms_error(FORKERROR, NULL, 1);
		exit(1);
	}
	if (pid == 0)
		exit (1);
	waitpid(pid, NULL, 0);
	prompt->pid = pid - 1;
}

/*
 *	This function set a few variable needed for a proper program workflow
 */

static t_read	init_vars(t_read prompt, char *str)
{
	char	*n;

	str = getcwd(NULL, 0);
	str = ft_strjoin ("PWD=", str);
	ms_export(prompt.env, str, 0);
	free (str);
	str = search_env(prompt.env, "SHLVL");
	if (!str || ft_atoi(str) <= 0)
		n = ft_strdup("1");
	else
		n = ft_itoa(ft_atoi(str) + 1);
	free (str);
	n = ft_strjoin("SHLVL=", n);
	ms_export(prompt.env, n, 0);
	free (n);
	return (prompt);
}

/*
 *	This function initialize everything for the t_read variable, which means 
 *	env variable, g_status and pid
 */
static	t_read	init_prompt(char **env)
{
	t_read	prompt;
	char	*str;

	str = NULL;
	prompt.cmd = NULL;
	prompt.env = env_set(env);
	g_status = 0;
	ms_getpid(&prompt);
	prompt = init_vars(prompt, str);
	return (prompt);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*out;
	t_read	prompt;

	(void)argc;
	(void)argv;
	prompt = init_prompt(env);
	while (1)
	{
		signal(SIGINT, sg_handle);
		signal(SIGQUIT, SIG_IGN);
		out = readline("El Nano🇪🇸 $ ");
		if (!check_args(out, &prompt))
			break ;
	}
	exit(g_status);
}
