/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:01:03 by akent-go          #+#    #+#             */
/*   Updated: 2023/08/09 17:04:01 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 *	This function will return the number of  quotes that we have to trim
 */

static int	trim_len(const char *s)
{
	int	ct;
	int	i;
	int	qte[2];

	i = 0;
	ct = 0;
	qte[0] = 0;
	qte[1] = 0;
	while (s && s[i])
	{
		qte[0] = (qte[0] + (!qte[1] && s[i] == '\'')) % 2;
		qte[1] = (qte[1] + (!qte[0] && s[i] == '\"')) % 2;
		if ((s[i] == '\"' && !qte[0]) || (s[i] == '\'' && !qte[1]))
			ct++;
		i++;
	}
	if (qte[0] || qte[1])
		return (-1);
	return (ct);
}

/*
 *	This function removes any unnecessary quote an return the "clean" string
 */

char	*ft_trim(const char *s, int qte[2])
{
	int		ct;
	int		i[2];
	char	*trim;

	i[0] = 0;
	i[1] = -1;
	ct = trim_len(s);
	if (!s || ct == -1)
		return (NULL);
	trim = malloc(sizeof(char) * (ft_strlen(s) - ct + 1));
	if (!trim)
		return (NULL);
	while (s[i[0]])
	{
		qte[0] = (qte[0] + (!qte[1] && s[i[0]] == '\'')) % 2;
		qte[1] = (qte[1] + (!qte[0] && s[i[0]] == '\"')) % 2;
		if ((s[i[0]] != '\"' || qte[0]) && (s[i[0]] != '\'' \
			|| qte[1]) && ++i[1] >= 0)
			trim[i[1]] = s[i[0]];
		i[0]++;
	}
	trim[++i[1]] = '\0';
	return (trim);
}
