/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 13:22:46 by msnow-be          #+#    #+#             */
/*   Updated: 2018/12/17 18:01:13 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_pointer_length(void *ptr)
{
	unsigned long long	value;
	int					length;

	value = (unsigned long long)ptr;
	length = 3;
	while (value / 16 != 0)
	{
		value /= 16;
		length++;
	}
	return (length);
}

int			get_pointer_print_width(t_format format)
{
	if (format.width > format.precision + 2)
		return (format.width);
	else
		return (format.precision + 2);
}

int			print_pointer(void *ptr, t_format format)
{
	int		print_width;
	int		num_width;
	int		pointer_length;

	print_width = get_pointer_print_width(format);
	pointer_length = get_pointer_length(ptr);
	if ((unsigned long long)ptr == 0 && format.precision == 0)
		num_width = 2;
	else
		num_width = (format.precision + 2 > pointer_length
			? format.precision + 2 : pointer_length);
	if (!(format.left_align) && (print_width > num_width))
		put_fill(' ', print_width - num_width);
	write(1, "0x", 2);
	if (format.precision + 2 > pointer_length)
		put_fill('0', format.precision + 2 - pointer_length);
	if (!((unsigned long long)ptr == 0 && format.precision == 0))
		put_unsigned_nbr_pure((unsigned long long)ptr, 16, 'x');
	if (format.left_align && (print_width > num_width))
		put_fill(' ', print_width - num_width);
	return (print_width > num_width ? print_width : num_width);
}
