/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 14:48:04 by msnow-be          #+#    #+#             */
/*   Updated: 2018/12/20 14:53:19 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			print_handler(va_list params, t_format format)
{
	int symbols_printed;

	symbols_printed = 0;
	if (format.data_type == 'd')
		symbols_printed = process_signed_int(params, format);
	else if (format.data_type == 'f')
		symbols_printed = process_float_number(params, format);
	else if (format.data_type == 'u')
		symbols_printed = process_unsigned_int(params, format);
	else if (format.data_type == 'c')
		symbols_printed = print_chars(va_arg(params, int), format);
	else if (format.data_type == 's')
		symbols_printed = print_string(va_arg(params, char *), format);
	else if (format.data_type == 'p')
		symbols_printed = print_pointer(va_arg(params, void *), format);
	else if (format.data_type == 'k')
		symbols_printed = print_date(va_arg(params, char *), format);
	else if (format.data_type == '%')
		symbols_printed = print_chars('%', format);
	else if (format.data_type != '\0')
		symbols_printed = print_chars(format.data_type, format);
	return (symbols_printed);
}

void		set_default_parameters(t_format *format)
{
	(*format).num_length[0] = '\0';
	(*format).num_length[1] = '\0';
	(*format).num_base = 10;
	(*format).hex_lettercase = 0;
	(*format).width = -1;
	(*format).precision = -1;
	(*format).left_align = 0;
	(*format).filler = ' ';
	(*format).plus_indication = 0;
	(*format).needs_prefix = 0;
	(*format).scientific_notation = 0;
}

t_format	get_print_format(const char *str, int *pos, va_list params)
{
	char		c;
	t_format	result;

	set_default_parameters(&result);
	c = str[*pos];
	while (c == 'l' || c == 'h' || c == 'L' || c == 'z' || c == 'j'
		|| c == '.' || (c >= '0' && c <= '9') || c == '#' || c == ' '
		|| c == '+' || c == '-' || c == '*')
	{
		if (c == 'l' || c == 'h' || c == 'L' || c == 'z' || c == 'j')
			update_num_length(str, pos, result.num_length);
		else if (c == '.' || (c >= '1' && c <= '9'))
			get_width_and_precision(str, pos, &result, params);
		else
		{
			set_extra_parameters(&result, c, params);
			*pos += 1;
		}
		c = str[*pos];
	}
	get_data_type_base_lettercase(c, &result);
	if (str[*pos] == '\0')
		*pos -= 1;
	return (result);
}

int			do_the_print(const char *str, int *pos, va_list params)
{
	t_format	print_format;

	*pos += 1;
	print_format = get_print_format(str, pos, params);
	return (print_handler(params, print_format));
}

int			ft_printf(const char *str, ...)
{
	va_list		params;
	int			pos;
	int			symbols_printed;

	pos = 0;
	symbols_printed = 0;
	va_start(params, str);
	while (str[pos] != '\0')
	{
		if (str[pos] == '%')
			symbols_printed += do_the_print(str, &pos, params);
		else if (str[pos] == '{')
			switch_formatting(str, &pos, &symbols_printed);
		else
		{
			write(1, &str[pos], 1);
			symbols_printed++;
		}
		pos++;
	}
	va_end(params);
	return (symbols_printed);
}
