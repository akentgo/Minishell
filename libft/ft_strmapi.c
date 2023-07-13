/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 13:14:13 by asolano-          #+#    #+#             */
/*   Updated: 2022/04/27 10:42:33 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Esta función aplica la función f dada como parámetro a cada caracter de la 
 * string s, genera una nueva string con el resultado de usar la función*/
#include"libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	i = 0;
	if (!s || (!s && !f))
		return (ft_strdup(""));
	else if (!f)
		return (ft_strdup(s));
	str = ft_strdup(s);
	if (!str)
		return (str = 0);
	while (s[i])
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	return (str);
}
