/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_signed_intgrs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 13:25:34 by msnow-be          #+#    #+#             */
/*   Updated: 2018/12/18 15:38:48 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		put_fill(char filler, int diff)
{
	while (diff-- > 0)
		write(1, &filler, 1);
}

void		put_sign(long long n, t_format format)
{
	if (n < 0)
		ft_putchar('-');
	else if (format.plus_indication == '+')
		ft_putchar('+');
	else if (format.plus_indication == ' ')
		ft_putchar(' ');
}

void		handle_sign_and_left_fill(long long n, t_format format,
				int diff)
{
	if (format.filler == ' ')
	{
		if (!(format.left_align))
			put_fill(format.filler, diff);
		put_sign(n, format);
	}
	else if (format.filler == '0')
	{
		put_sign(n, format);
		if (!format.left_align || format.precision > format.width)
			put_fill(format.filler, diff);
	}
}

void		put_signed_nbr_pure(long long n)
{
	char	c;

	if (n == -9223372036854775807LL - 1)
	{
		ft_putstr_till_pos("9223372036854775808", 20);
		return ;
	}
	if (n < 0)
		n *= -1;
	if (n / 10 != 0)
		put_signed_nbr_pure(n / 10);
	c = n % 10 + '0';
	ft_putchar(c);
}

int			put_signed_nbr(long long n, t_format format)
{
	int		print_width;
	int		digits_width;
	int		extras_width;
	int		num_width;

	if (format.precision != -1)
		format.filler = ' ';
	print_width = get_print_width(format);
	digits_width = get_signed_digits_width(n, format.precision);
	extras_width = get_signed_extras_width(n, format);
	num_width = (format.precision > digits_width
		? format.precision + extras_width : digits_width + extras_width);
	handle_sign_and_left_fill(n, format, print_width - num_width);
	if (format.precision > digits_width)
		put_fill('0', format.precision - digits_width);
	if (!(n == 0 && format.precision == 0))
		put_signed_nbr_pure(n);
	if (format.left_align && (print_width > num_width))
		put_fill(' ', print_width - num_width);
	return (print_width > num_width ? print_width : num_width);
}
