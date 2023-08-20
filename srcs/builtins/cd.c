/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:17:24 by akent-go          #+#    #+#             */
/*   Updated: 2023/08/09 17:04:27 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_cd(t_read *p)
{
	char	**str[2];
	char	*aux;

	g_status = 0;
	str[0] = ((t_ms *)p->cmd->content)->cmd;
	aux = search_env(p->env, "HOME");
	if (!aux)
		aux = ft_strdup("");
	str[1] = ft_expand_arr(NULL, aux);
	free (aux);
	aux = getcwd(NULL, 0);
	str[1] = ft_expand_arr(str[1], aux);
	free(aux);
	cd_error(str);
	if (!g_status)
		ms_export1(p->env, set_var("OLDPWD", str[1][1]));
	aux = getcwd(NULL, 0);
	if (!aux)
		aux = ft_strdup("");
	str[1] = ft_expand_arr(str[1], aux);
	free (aux);
	ms_export1(p->env, set_var("PWD", str[1][2]));
	ft_free_matrix(&str[1]);
	return (g_status);
}
