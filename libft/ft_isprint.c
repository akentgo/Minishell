/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 09:52:02 by asolano-          #+#    #+#             */
/*   Updated: 2022/04/27 08:50:49 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*Esta función comprueba que el carácter introducido es imprimible, devuelve 1
 * si lo es y 0 si no*/
int	ft_isprint(int a)
{
	if (a >= 32 && a <= 126)
		return (1);
	else
		return (0);
}
