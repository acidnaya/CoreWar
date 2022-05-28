/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:45:24 by msnow-be          #+#    #+#             */
/*   Updated: 2018/11/19 16:49:08 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *current_list;
	t_list *result;

	if (lst)
	{
		if (!(result = f(lst)))
			return (NULL);
		else
			current_list = result;
		while (lst->next)
		{
			lst = lst->next;
			if (!(current_list->next = f(lst)))
				return (NULL);
			else
				current_list = current_list->next;
		}
		return (result);
	}
	return (NULL);
}
