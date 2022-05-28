/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:45:24 by msnow-be          #+#    #+#             */
/*   Updated: 2018/11/19 16:49:08 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ans;
	unsigned int	pos;

	if (s == (NULL))
		return (NULL);
	if (!(ans = (char *)malloc((ft_strlen(s) + 1) * sizeof(char))))
		return (NULL);
	pos = 0;
	while (s[pos])
	{
		ans[pos] = f(pos, s[pos]);
		pos++;
	}
	ans[pos] = '\0';
	return (ans);
}
