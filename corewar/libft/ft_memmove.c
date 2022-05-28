/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:45:24 by msnow-be          #+#    #+#             */
/*   Updated: 2018/11/19 16:49:08 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t num)
{
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;
	size_t			pos;

	dst_ptr = (unsigned char*)destination;
	src_ptr = (unsigned char*)source;
	if (destination < source)
	{
		pos = 0;
		while (pos < num)
		{
			dst_ptr[pos] = src_ptr[pos];
			pos++;
		}
	}
	else
	{
		pos = num;
		while (pos-- > 0)
			dst_ptr[pos] = src_ptr[pos];
	}
	return (destination);
}
