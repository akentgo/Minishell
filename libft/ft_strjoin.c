/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 09:28:18 by asolano-          #+#    #+#             */
/*   Updated: 2023/07/30 11:39:26 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Esta función coge s1 y s2, las concatena en una string y te devuelve esa nueva
 * string*/

#include"libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		a_cont;
	int		sol_cont;
	char	*sol;

	a_cont = 0;
	sol_cont = 0;
	sol = (char *)malloc(sizeof (char) * ((ft_strlen(s1) + ft_strlen(s2) + 1)));
	if (!sol)
		return (0);
	while (s1 && s1[sol_cont])
	{
		sol[sol_cont] = s1[sol_cont];
		sol_cont++;
	}
	while (s2 && s2[a_cont])
	{
		sol[sol_cont] = s2[a_cont];
		a_cont++;
		sol_cont++;
	}
	sol[sol_cont] = '\0';
	return (sol);
}
/*
char	*ft_emptycmp(const char *s1, const char *s2);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		i;
	int		j;

	j = 0;
	i = 0;
	ft_emptycmp(s1, s2);
	newstr = malloc(sizeof (char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!newstr)
		return (0);
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[j])
		newstr[i++] = s2[j++];
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_emptycmp(const char *str1, const char *str2)
{
	if (!str1 && !str2)
		return (ft_strdup(""));
	else
		return (0);
}*/
