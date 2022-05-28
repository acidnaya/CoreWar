/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:33:36 by msnow-be          #+#    #+#             */
/*   Updated: 2018/12/20 14:34:07 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		process_signed_int(va_list params, t_format format)
{
	long long value;

	if (format.num_length[0] == '\0')
		value = va_arg(params, int);
	else if (!ft_strncmp(format.num_length, "hh", 2))
		value = (char)va_arg(params, int);
	else if (!ft_strncmp(format.num_length, "h", 1))
		value = (short)va_arg(params, int);
	else if (!ft_strncmp(format.num_length, "ll", 2)
		|| !ft_strncmp(format.num_length, "j", 1)
		|| !ft_strncmp(format.num_length, "z", 1))
		value = va_arg(params, long long);
	else if (!ft_strncmp(format.num_length, "l", 1))
		value = va_arg(params, long);
	else
		return (0);
	return (put_signed_nbr(value, format));
}

int		process_unsigned_int(va_list params, t_format format)
{
	unsigned long long	value;

	if (format.num_length[0] == '\0')
		value = va_arg(params, unsigned int);
	else if (!ft_strncmp(format.num_length, "hh", 2))
		value = (unsigned char)va_arg(params, int);
	else if (!ft_strncmp(format.num_length, "h", 1))
		value = (unsigned short)va_arg(params, int);
	else if (!ft_strncmp(format.num_length, "ll", 2)
		|| !ft_strncmp(format.num_length, "j", 1)
		|| !ft_strncmp(format.num_length, "z", 1))
		value = va_arg(params, unsigned long long);
	else if (!ft_strncmp(format.num_length, "l", 1))
		value = va_arg(params, unsigned long);
	else
		return (0);
	return (put_unsigned_nbr(value, format));
}

int		process_float_number(va_list params, t_format format)
{
	if (format.num_length[0] == '\0'
		|| !ft_strncmp(format.num_length, "l", 1))
		return (put_double(va_arg(params, double), format));
	else if (!ft_strncmp(format.num_length, "L", 1))
		return (put_long_double(va_arg(params, long double), format));
	else
		return (0);
}
