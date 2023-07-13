/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 08:57:41 by asolano-          #+#    #+#             */
/*   Updated: 2022/05/05 08:28:32 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (lst == 0)
	{
		return ;
	}
	next = (*lst)->next;
	while (next != 0)
	{
		ft_lstdelone(*lst, del);
		*lst = next;
		next = (*lst)->next;
	}
	ft_lstdelone(*lst, del);
	*lst = 0;
}
