/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:45:24 by msnow-be          #+#    #+#             */
/*   Updated: 2018/11/19 16:49:08 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*ans;
	int		pos;

	ans = (char*)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (ans == NULL)
	{
		return (NULL);
	}
	pos = 0;
	while (src[pos] != '\0')
	{
		ans[pos] = src[pos];
		pos++;
	}
	ans[pos] = '\0';
	return (ans);
}
