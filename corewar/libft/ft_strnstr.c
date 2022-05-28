/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 13:41:43 by msnow-be          #+#    #+#             */
/*   Updated: 2018/11/20 13:53:21 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t			pos1;
	size_t			pos2;

	pos1 = 0;
	while ((big[pos1] != '\0') && (pos1 < len))
	{
		pos2 = 0;
		while ((big[pos1 + pos2] == little[pos2]) && (little[pos2] != '\0')
			&& (pos1 + pos2 < len))
		{
			pos2++;
		}
		if (little[pos2] == '\0')
			return ((char *)(big + pos1));
		pos1++;
	}
	return (NULL);
}
