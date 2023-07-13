/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:13:10 by asolano-          #+#    #+#             */
/*   Updated: 2023/01/31 16:32:13 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Esta función compara n caracteres de los dos strings y devuelve la diferencia
 *  entre el primer caracter que no sea igual, si son iguales devuelve 0*/
#include"libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	comp;

	comp = 0;
	if	(n == 0)
		return (0);
	while (n > 0)
	{
		if (!(*s1) && (*s1 == *s2))
			return (0);
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}*/
