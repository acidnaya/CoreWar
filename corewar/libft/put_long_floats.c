/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_long_floats.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 13:25:34 by msnow-be          #+#    #+#             */
/*   Updated: 2018/12/20 14:14:01 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_long_fractional_part(double fract_part, int precision)
{
	while (precision--)
	{
		fract_part *= 10;
		if ((long long)fract_part == 0)
			write(1, "0", 1);
	}
	if (fract_part - (long long)fract_part <= 0.5)
		fract_part = (long long)fract_part;
	else
		fract_part = (long long)fract_part + 1;
	if (fract_part != 0)
		put_unsigned_nbr_pure(fract_part, 10, 0);
}

void	get_long_int_part_and_exponent(long double *n, int *int_part,
		int *exponent, t_format format)
{
	*int_part = (((int)*n) >= 0 ? ((int)*n) : ((int)*n) * -1);
	*exponent = 0;
	if (format.scientific_notation)
	{
		while (*int_part >= 10)
		{
			*n /= 10;
			*exponent += 1;
			*int_part = (((int)*n) >= 0 ? ((int)*n) : ((int)*n) * -1);
		}
		while (*int_part == 0)
		{
			*n *= 10;
			*exponent -= 1;
			*int_part = (((int)*n) >= 0 ? ((int)*n) : ((int)*n) * -1);
		}
	}
}

int		put_long_double(long double n, t_format format)
{
	int			int_part;
	int			exponent;
	int			print_width;
	int			num_width;

	format.precision = (format.precision == -1 ? 6 : format.precision);
	print_width = format.width;
	num_width = get_double_width(n, format);
	get_long_int_part_and_exponent(&n, &int_part, &exponent, format);
	handle_sign_and_left_fill((int)n, format, print_width - num_width);
	put_signed_nbr_pure(int_part);
	if (format.precision > 0 ||
		(format.precision == 0 && format.scientific_notation))
		write(1, ".", 1);
	if (format.precision > 0)
		put_long_fractional_part(n - (int)n, format.precision);
	if (format.scientific_notation)
	{
		write(1, "e", 1);
		ft_printf("%+.2d", exponent);
	}
	if (format.left_align && (print_width > num_width))
		put_fill(' ', print_width - num_width);
	return (print_width > num_width ? print_width : num_width);
}

void	update_long_precision_by_significance(long double n, int *precision)
{
	long double	fract_part;
	int			confirmed_precision;

	confirmed_precision = 0;
	fract_part = n - (int)n;
	while (confirmed_precision < *precision)
	{
		confirmed_precision++;
		fract_part *= 10.0;
	}
	if (((int)fract_part) % 10)
		return ;
	while (((int)fract_part != 0) && confirmed_precision > 0)
	{
		confirmed_precision--;
		if (fract_part - (int)fract_part >= 0.5)
			break ;
		fract_part /= 10.0;
	}
	*precision = confirmed_precision + 1;
}
