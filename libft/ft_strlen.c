/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:01:04 by asolano-          #+#    #+#             */
/*   Updated: 2023/07/30 11:36:00 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*Esta función mide cuantos caracteres tiene una cadena y devuelve la longitud*/
size_t	ft_strlen(const char *a)
{
	int	l;

	l = 0;
	if (!a)
		return (0);
	while (*a != '\0')
	{
		l++;
		a++;
	}
	return (l);
}
