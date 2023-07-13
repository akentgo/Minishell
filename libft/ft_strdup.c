/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:33:01 by asolano-          #+#    #+#             */
/*   Updated: 2022/04/27 10:13:12 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Esta función aloja suficiente memoria para copiar s1, hace la copia y devuelve
 * un puntero al string, si no hay suficiente memoria devuelve NULL*/
#include"libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	str_length;

	if (!s1)
		return (NULL);
	str_length = ft_strlen(s1);
	s2 = malloc(sizeof (char) * str_length + 1);
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, str_length + 1);
	return (s2);
}
