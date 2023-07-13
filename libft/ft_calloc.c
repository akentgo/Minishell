/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 08:54:26 by asolano-          #+#    #+#             */
/*   Updated: 2022/05/06 10:04:05 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Esta función aloja de forma contigua espacio para count objetos que son size 
 * bytes de memoria y devuelve un puntero a la memoria alojada, esta memoria se
 * llena con bytes de valor 0*/
#include"libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	if (count + size < count || count + size < size)
		return (0);
	ptr = (char *) malloc(count * size);
	if (ptr == 0)
		return (0);
	i = 0;
	while (i < (count * size))
		ptr[i++] = 0;
	return ((void *) ptr);
}
