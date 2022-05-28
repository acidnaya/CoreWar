/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:45:24 by msnow-be          #+#    #+#             */
/*   Updated: 2018/11/19 16:49:08 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*ans;
	unsigned int	pos;

	if (s == NULL)
		return (NULL);
	if (!(ans = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	pos = start;
	while (s[pos] && (pos < start + len))
	{
		ans[pos - start] = s[pos];
		pos++;
	}
	ans[pos - start] = '\0';
	return (ans);
}
