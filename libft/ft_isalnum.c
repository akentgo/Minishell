/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 09:44:12 by asolano-          #+#    #+#             */
/*   Updated: 2023/01/31 16:31:24 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Esta función comprueba que el carácter introducido es una letra o un número,
 *devuelve 1 * si lo es y 0 si no*/
int	ft_isalnum(int a)
{
	if ((a >= '0' && a <= '9' ) || (a >= 'a' && a <= 'z')
		|| (a >= 'A' && a <= 'Z'))
		return (1);
	else
		return (0);
}
