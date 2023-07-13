/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:08:31 by asolano-          #+#    #+#             */
/*   Updated: 2022/04/21 12:39:50 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Esta función sustituye n veces el caracter c en la cadena str*/
#include"libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	while (n > 0)
	{
		((char *)str)[n - 1] = c;
		n--;
	}
	return (str);
}
