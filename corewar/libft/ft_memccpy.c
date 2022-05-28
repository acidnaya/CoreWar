/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:45:24 by msnow-be          #+#    #+#             */
/*   Updated: 2018/11/19 16:49:08 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *source, int c, size_t count)
{
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;
	size_t			pos;

	pos = 0;
	dst_ptr = (unsigned char*)dest;
	src_ptr = (unsigned char*)source;
	while (pos < count)
	{
		dst_ptr[pos] = src_ptr[pos];
		if (src_ptr[pos] == (unsigned char)c)
			return ((void*)(dst_ptr + pos + 1));
		pos++;
	}
	return (NULL);
}
