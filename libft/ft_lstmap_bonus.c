/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:22:57 by asolano-          #+#    #+#             */
/*   Updated: 2022/05/05 08:30:34 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*node;

	if (lst == 0)
		return (0);
	newlist = ft_lstnew(f(lst->content));
	if (newlist == 0)
		return (0);
	node = newlist;
	while (lst->next)
	{
		node->next = ft_lstnew(f(lst->content));
		if (node->next == 0)
		{
			ft_lstclear(&newlist, del);
			return (0);
		}
		node = node->next;
		lst = lst->next;
	}
	return (newlist);
}
