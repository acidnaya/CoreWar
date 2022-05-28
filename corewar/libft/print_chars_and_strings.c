/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_chars_and_strings.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:24:01 by msnow-be          #+#    #+#             */
/*   Updated: 2018/12/19 18:56:31 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_char_width(wchar_t c)
{
	if (c <= 0x7F)
		return (1);
	else if (c <= 0x7FF)
		return (2);
	else if (c <= 0x7FFFF)
		return (3);
	else if (c <= 0x10FFFF)
		return (4);
	else
		return (0);
}

void	ft_putwchar(wchar_t c)
{
	if (c <= 0x7F)
		ft_putchar(c);
	else if (c <= 0x7FF)
	{
		ft_putchar((c >> 6) + 0xC0);
		ft_putchar((c & 0x3F) + 0x80);
	}
	else if (c <= 0x7FFFF)
	{
		ft_putchar((c >> 12) + 0xE0);
		ft_putchar(((c >> 6) & 0x3F) + 0x80);
		ft_putchar((c & 0x3F) + 0x80);
	}
	else if (c <= 0x10FFFF)
	{
		ft_putchar((c >> 18) + 0xF0);
		ft_putchar(((c >> 12) & 0x3F) + 0x80);
		ft_putchar(((c >> 6) & 0x3F) + 0x80);
		ft_putchar((c & 0x3F) + 0x80);
	}
}

int		print_chars(wchar_t c, t_format format)
{
	int		print_width;
	int		char_width;

	if (format.num_length[0] == '\0')
		c = (char)c;
	if (c == 0 && format.width == -1)
		print_width = 1;
	else
		print_width = format.width;
	char_width = get_char_width(c);
	if (!(format.left_align) && (print_width > char_width))
		put_fill(format.filler, print_width - char_width);
	ft_putwchar(c);
	if (format.left_align && (print_width > char_width))
		put_fill(' ', print_width - char_width);
	return (print_width > char_width ? print_width : char_width);
}

int		print_string(char *str, t_format format)
{
	int		print_width;
	int		str_width;
	int		string_length;

	if (!str)
		str = "(null)";
	string_length = (int)ft_strlen(str);
	if (format.precision > string_length)
		format.precision = string_length;
	print_width = get_print_width(format);
	if (str[0] == '\0' && format.width == -1)
		print_width = 0;
	if (format.precision != -1 && string_length > format.precision)
		str_width = format.precision;
	else
		str_width = string_length;
	if (!(format.left_align) && (print_width > str_width))
		put_fill(format.filler, print_width - str_width);
	ft_putstr_till_pos(str, str_width);
	if (format.left_align && (print_width > str_width))
		put_fill(' ', print_width - str_width);
	return (print_width > str_width ? print_width : str_width);
}
