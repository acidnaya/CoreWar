/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 14:48:04 by msnow-be          #+#    #+#             */
/*   Updated: 2018/12/20 13:17:42 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		get_length_rating(char *length)
{
	if (!ft_strncmp(length, "hh", 2))
		return (0);
	else if (!ft_strncmp(length, "h", 1))
		return (1);
	else if (!ft_strncmp(length, "ll", 2) || !ft_strncmp(length, "j", 1)
		|| !ft_strncmp(length, "z", 1))
		return (3);
	else if (!ft_strncmp(length, "l", 1))
		return (2);
	else
		return (-1);
}

static _Bool	new_length_is_bigger(char *new, char *old)
{
	int	new_rating;
	int	old_rating;

	new_rating = get_length_rating(new);
	old_rating = get_length_rating(old);
	if (new_rating > old_rating)
		return (1);
	else
		return (0);
}

void			update_num_length(const char *str, int *pos, char *length)
{
	int		type_length;
	char	result[2];
	char	type_char;

	type_length = 0;
	type_char = str[*pos];
	while (str[*pos + type_length] == type_char && type_length < 2)
	{
		result[type_length] = type_char;
		type_length++;
	}
	*pos += type_length;
	if (length && length[0] != '\0')
	{
		if (new_length_is_bigger(result, length))
		{
			length[0] = result[0];
			length[1] = result[1];
		}
	}
	else
	{
		length[0] = result[0];
		length[1] = result[1];
	}
}

void			get_width_and_precision(const char *str, int *pos,
					t_format *result, va_list params)
{
	if (str[*pos] != '.')
		(*result).width = ft_atoi(str + *pos);
	while (str[*pos] >= '0' && str[*pos] <= '9')
		*pos += 1;
	if (str[*pos] == '.')
	{
		*pos += 1;
		if (str[*pos] != '*')
		{
			(*result).precision = ft_atoi(str + *pos);
			while (str[*pos] >= '0' && str[*pos] <= '9')
				*pos += 1;
		}
		else
		{
			(*result).precision = va_arg(params, int);
			if ((*result).precision < 0)
				(*result).precision = -1;
			*pos += 1;
		}
	}
}

void			set_extra_parameters(t_format *format, char c, va_list params)
{
	if (c == '-')
		(*format).left_align = 1;
	else if (c == '0')
		(*format).filler = '0';
	else if (c == '+')
		(*format).plus_indication = '+';
	else if (c == ' ')
	{
		if ((*format).plus_indication != '+')
			(*format).plus_indication = ' ';
	}
	else if (c == '#')
		(*format).needs_prefix = 1;
	else if (c == '*')
	{
		(*format).width = va_arg(params, int);
		if ((*format).width < 0)
		{
			(*format).width *= -1;
			(*format).left_align = 1;
		}
	}
}
