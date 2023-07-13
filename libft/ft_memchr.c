/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 08:42:45 by asolano-          #+#    #+#             */
/*   Updated: 2022/05/06 09:46:37 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Esta función busca la primera aparición de un caracter en un string, si el
 * caracter a buscar es '\0' también lo encontrará, devolverá un puntero al 
 * caracter si lo encuentra o 0 si no lo encuentra*/
#include"libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char) c)
			return ((void *) &str[i]);
		i++;
	}
	return (0);
}
