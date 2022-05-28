/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_funcs_part1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 14:48:04 by msnow-be          #+#    #+#             */
/*   Updated: 2019/02/18 16:30:56 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_printf.h"

void	ft_putstr_till_pos(char const *s, int len)
{
	int pos;

	if (s != NULL)
	{
		pos = 0;
		while (s[pos] != '\0' && pos < len)
		{
			ft_putwchar(s[pos]);
			pos++;
		}
	}
}
