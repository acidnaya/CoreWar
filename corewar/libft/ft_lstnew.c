/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:45:24 by msnow-be          #+#    #+#             */
/*   Updated: 2018/11/19 16:49:08 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new_list;

	if (!(new_list = malloc(sizeof(t_list))))
		return (NULL);
	if (content)
	{
		new_list->content = ft_memalloc(content_size);
		ft_memcpy(new_list->content, content, content_size);
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
