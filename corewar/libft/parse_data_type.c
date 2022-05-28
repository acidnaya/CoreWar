/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:39:38 by msnow-be          #+#    #+#             */
/*   Updated: 2018/12/20 14:15:25 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		get_info_for_float(char c, t_format *format)
{
	(*format).data_type = 'f';
	(*format).scientific_notation = (c == 'e' ? 1 : 0);
}

static void		get_info_for_unsigned(char c, t_format *format)
{
	(*format).data_type = 'u';
	if (c == 'o')
		(*format).num_base = 8;
	else if (c == 'b')
		(*format).num_base = 2;
	else if ((c == 'x') || (c == 'X'))
	{
		(*format).num_base = 16;
		(*format).hex_lettercase = c;
	}
}

void			get_data_type_base_lettercase(char c, t_format *format)
{
	if (c == 'd' || c == 'i')
		(*format).data_type = 'd';
	else if (c == 'f' || c == 'e')
		get_info_for_float(c, format);
	else if (c == 'u' || c == 'o' || c == 'x' || c == 'X' || c == 'b')
		get_info_for_unsigned(c, format);
	else if (c == 'c' || c == 'C')
	{
		(*format).data_type = 'c';
		if (c == 'C')
		{
			(*format).num_length[0] = 'l';
			(*format).num_length[1] = '\0';
		}
	}
	else
		(*format).data_type = c;
}
