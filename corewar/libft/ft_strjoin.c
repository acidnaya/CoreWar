/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:45:24 by msnow-be          #+#    #+#             */
/*   Updated: 2018/11/19 16:49:08 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ans;
	size_t	pos;
	size_t	size_s1;

	if ((s1 == NULL) || (s2 == NULL))
		return (NULL);
	size_s1 = ft_strlen(s1);
	if (!(ans = (char *)malloc((size_s1 + ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	pos = 0;
	while (s1[pos])
	{
		ans[pos] = s1[pos];
		pos++;
	}
	while (s2[pos - size_s1])
	{
		ans[pos] = s2[pos - size_s1];
		pos++;
	}
	ans[pos] = '\0';
	return (ans);
}
