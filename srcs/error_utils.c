/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:45:44 by akent-go          #+#    #+#             */
/*   Updated: 2023/07/30 17:47:12 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	ft_free_matrix(char ***matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[0] && matrix[0][i])
	{
		free (matrix[0][i]);
		i++;
	}
	if (matrix)
	{
		free (matrix[0]);
		*matrix = NULL;
	}
}

int	ft_matrixlen(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return (0);
	while (matrix[i])
		i++;
	return (i);
}

char	**dup_matrix(char **matrix)
{
	char	**new_matrix;
	int		i;

	i = -1;
	new_matrix = malloc(sizeof (char *) * (ft_matrixlen(matrix) + 1));
	if (!new_matrix)
		return (NULL);
	while (matrix[++i])
		new_matrix[i] = ft_strdup(matrix[i]);
	new_matrix[i] = NULL;
	return (new_matrix);
}
