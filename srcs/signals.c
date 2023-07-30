/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:15:13 by akent-go          #+#    #+#             */
/*   Updated: 2023/07/30 18:15:13 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sg_handle(int sig)
{
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
	printf("\033[K\n");
	rl_on_new_line();
	rl_redisplay();
}
