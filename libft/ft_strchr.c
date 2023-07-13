/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 08:42:45 by asolano-          #+#    #+#             */
/*   Updated: 2022/05/06 10:01:32 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Esta función busca la primera aparición de un caracter en un string, si el
 * caracter a buscar es '\0' también lo encontrará, devolverá un puntero al 
 * caracter si lo encuentra o 0 si no lo encuentra*/
char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == (char) c)
			return (ptr);
		ptr++;
	}
	if (*ptr == (char) c)
		return (ptr);
	return (0);
}
