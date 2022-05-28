/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_unsigned_intgrs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 13:25:34 by msnow-be          #+#    #+#             */
/*   Updated: 2018/12/18 13:07:07 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		put_base_id(t_format format)
{
	if (format.needs_prefix)
	{
		if (format.num_base == 8 || format.num_base == 16)
			write(1, "0", 1);
		if (format.num_base == 16)
			write(1, &format.hex_lettercase, 1);
	}
}

void		handle_unsigned_left_fill(unsigned long long n, t_format format,
				int diff)
{
	if (format.filler == ' ')
	{
		if (!(format.left_align))
			put_fill(format.filler, diff);
		if (n > 0)
			put_base_id(format);
	}
	else if (format.filler == '0')
	{
		if (n > 0)
			put_base_id(format);
		if (!(format.left_align))
			put_fill(format.filler, diff);
	}
}

void		put_unsigned_nbr_pure(unsigned long long n, int base,
			char lettercase)
{
	char	c;

	if (n / base != 0)
		put_unsigned_nbr_pure(n / base, base, lettercase);
	c = n % base + '0';
	if ((base > 10) && (n % base > 9))
	{
		if (lettercase == 'X')
			c += 'A' - 10 - '0';
		if (lettercase == 'x')
			c += 'a' - 10 - '0';
	}
	ft_putchar(c);
}

int			put_unsigned_nbr(unsigned long long n, t_format format)
{
	int		print_width;
	int		digits_width;
	int		extras_width;
	int		num_width;

	if (format.precision != -1)
		format.filler = ' ';
	digits_width = get_unsigned_digits_width(n, format);
	if (format.num_base == 8 && format.precision > digits_width)
		format.needs_prefix = 0;
	print_width = get_print_width(format);
	extras_width = get_unsigned_extras_width(n, format);
	num_width = (format.precision > digits_width
		? format.precision + extras_width : digits_width + extras_width);
	handle_unsigned_left_fill(n, format, print_width - num_width);
	if (format.precision > digits_width)
		put_fill('0', format.precision - digits_width);
	if (!(n == 0 && format.precision == 0) ||
		(n == 0 && format.num_base == 8 && format.needs_prefix == 1))
		put_unsigned_nbr_pure(n, format.num_base, format.hex_lettercase);
	if (format.left_align && (print_width > num_width))
		put_fill(' ', print_width - num_width);
	return (print_width > num_width ? print_width : num_width);
}
