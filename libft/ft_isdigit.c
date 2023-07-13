/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 08:50:46 by asolano-          #+#    #+#             */
/*   Updated: 2022/04/27 08:48:53 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*Esta función comprueba si el carácter dado es un número, si lo es devuelve 1,
 * si no 0 */
int	ft_isdigit(int n)
{
	if (n >= '0' && n <= '9')
		return (1);
	else
		return (0);
}
