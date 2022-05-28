/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_int_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 15:13:39 by msnow-be          #+#    #+#             */
/*   Updated: 2018/12/18 15:38:21 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_print_width(t_format format)
{
	if (format.width > format.precision)
		return (format.width);
	else
		return (format.precision);
}

int		get_signed_digits_width(long long int n, int precision)
{
	int	width;

	width = 0;
	if (n == 0 && precision == 0)
		return (width);
	while (n / 10 != 0)
	{
		width++;
		n /= 10;
	}
	return (width + 1);
}

int		get_signed_extras_width(long long int n, t_format format)
{
	int	width;

	width = 0;
	if (n < 0 || (n >= 0 && format.plus_indication != 0))
		width++;
	return (width);
}

int		get_unsigned_digits_width(unsigned long long int n, t_format format)
{
	int	width;

	width = 0;
	if ((n == 0 && format.precision == 0) &&
		!(format.num_base == 8 && format.needs_prefix == 1))
		return (width);
	while (n / format.num_base != 0)
	{
		width++;
		n /= format.num_base;
	}
	return (width + 1);
}

int		get_unsigned_extras_width(unsigned long long int n, t_format format)
{
	int	width;

	width = 0;
	if (format.needs_prefix != 0 && n > 0)
	{
		if (format.num_base == 16)
			width += 2;
		else if (format.num_base == 8)
			width++;
	}
	return (width);
}
