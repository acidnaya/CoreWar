/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:13:34 by msnow-be          #+#    #+#             */
/*   Updated: 2019/02/15 18:17:24 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		lst_len(t_list *lst)
{
	int len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

void	ft_lst_push_back(t_list *lst1, t_list *lst2)
{
	if (!lst1)
		return ;
	while (lst1->next)
		lst1 = lst1->next;
	lst1->next = lst2;
}
