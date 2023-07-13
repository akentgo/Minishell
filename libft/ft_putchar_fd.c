/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:52:39 by asolano-          #+#    #+#             */
/*   Updated: 2022/04/27 10:54:43 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Envía el caracter c al file descriptor especificado*/
#include"libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
