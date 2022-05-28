/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_double_width.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 15:13:39 by msnow-be          #+#    #+#             */
/*   Updated: 2018/12/17 14:39:11 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_double_width(double n, t_format format)
{
	int				width;
	int				int_part;

	if (format.scientific_notation == 0)
	{
		width = 1;
		if (n < 0 || (n >= 0 && format.plus_indication != 0))
			width++;
		int_part = (int)n;
		while (int_part / 10 != 0)
		{
			width++;
			int_part /= 10;
		}
		return (width + 1 + format.precision);
	}
	else
	{
		width = 6;
		if (n < 0 || (n >= 0 && format.plus_indication != 0))
			width++;
		return (width + format.precision);
	}
}
