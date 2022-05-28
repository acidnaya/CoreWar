/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_formatting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 14:17:35 by msnow-be          #+#    #+#             */
/*   Updated: 2018/12/20 14:52:26 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	switch_formatting(const char *str, int *pos, int *symbols_printed)
{
	if (!ft_strncmp(str + *pos + 1, "red}", 4))
		write(1, "\033[31m", 5);
	else if (!ft_strncmp(str + *pos + 1, "green}", 6))
		write(1, "\033[32m", 5);
	else if (!ft_strncmp(str + *pos + 1, "yellow}", 7))
		write(1, "\033[33m", 5);
	else if (!ft_strncmp(str + *pos + 1, "blue}", 5))
		write(1, "\033[34m", 5);
	else if (!ft_strncmp(str + *pos + 1, "magenta}", 7))
		write(1, "\033[35m", 5);
	else if (!ft_strncmp(str + *pos + 1, "cyan}", 5))
		write(1, "\033[36m", 5);
	else if (!ft_strncmp(str + *pos + 1, "black}", 6))
		write(1, "\033[30m", 5);
	else if (!ft_strncmp(str + *pos + 1, "white}", 6))
		write(1, "\033[37m", 5);
	else if (!ft_strncmp(str + *pos + 1, "eoc}", 4))
		write(1, "\033[0m", 4);
	else
	{
		write(1, &str[*pos], 1);
		*symbols_printed += 1;
		return ;
	}
	*pos = ft_strchr(str + *pos, '}') - str;
}
