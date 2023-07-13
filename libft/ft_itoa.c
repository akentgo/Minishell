/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 11:50:46 by asolano-          #+#    #+#             */
/*   Updated: 2022/04/28 12:53:22 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Esta función crea una string que representa el valor entero recibido como
 * argumento. Gestiona números negativos*/
#include"libft.h"

#define TAM 20

char	*ft_itoa(int n)
{
	char	str[TAM];
	int		sign;
	long	val;
	int		i;

	i = TAM - 1;
	sign = 0;
	val = (long) n;
	if (val < 0)
	{
		val = -val;
		sign = 1;
	}
	str[i--] = '\0';
	while (val > 0)
	{
		str[i--] = (char)(val % 10 + '0');
		val /= 10;
	}
	if (sign)
		str[i--] = '-';
	if (n == 0)
		str[i--] = '0';
	return (ft_strdup(&str[i + 1]));
}
