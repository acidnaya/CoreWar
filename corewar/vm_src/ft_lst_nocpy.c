/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_nocpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:45:24 by msnow-be          #+#    #+#             */
/*   Updated: 2019/02/14 16:13:41 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew_nocpy(void const *content, size_t content_size)
{
	t_list *new_list;

	if (!(new_list = malloc(sizeof(t_list))))
		return (NULL);
	if (content)
	{
		new_list->content = (void *)content;
		new_list->content_size = content_size;
	}
	else
	{
		new_list->content = (NULL);
		new_list->content_size = 0;
	}
	new_list->next = (NULL);
	return (new_list);
}

int		ft_list_len(t_list *lst)
{
	int result;

	result = 0;
	while (lst)
	{
		result++;
		lst = lst->next;
	}
	return (result);
}

void	ft_lstdelone_nocpy(t_list **alst)
{
	if (alst && *alst)
	{
		free(*alst);
		*alst = NULL;
	}
}

void	ft_lstdel_nocpy(t_list **alst)
{
	if (alst && *alst && (*alst)->next)
		ft_lstdel_nocpy(&(*alst)->next);
	ft_lstdelone_nocpy((&(*alst)));
}
