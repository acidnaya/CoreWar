/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:45:24 by msnow-be          #+#    #+#             */
/*   Updated: 2018/11/19 16:49:08 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t pos;
	size_t dest_size;

	pos = 0;
	while ((pos < n) && dest[pos] != '\0')
		pos++;
	if (pos == n)
		return (n + ft_strlen(src));
	dest_size = pos;
	while (pos < n - 1 && src[pos - dest_size] != '\0')
	{
		dest[pos] = src[pos - dest_size];
		pos++;
	}
	dest[pos] = '\0';
	return (dest_size + ft_strlen(src));
}
