/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:45:24 by msnow-be          #+#    #+#             */
/*   Updated: 2018/11/19 16:49:08 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_length(int n)
{
	int len;

	len = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char	*res;
	int		negative;
	int		len;
	int		pos;

	negative = 0;
	if (n < 0)
		negative = 1;
	len = get_length(n);
	if ((res = ft_strnew(len + negative)) == NULL)
		return (NULL);
	if (negative)
		res[0] = '-';
	pos = len + negative - 1;
	while (pos >= negative)
	{
		if (negative)
			res[pos--] = (n % 10 * -1) + '0';
		else
			res[pos--] = n % 10 + '0';
		n /= 10;
	}
	return (res);
}
