/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfriesen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:31:29 by jfriesen          #+#    #+#             */
/*   Updated: 2019/03/20 13:31:31 by jfriesen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include "libft.h"

int		is_spaces(char c)
{
	int		i;

	i = 0;
	while (SPACES[i])
	{
		if (c == SPACES[i])
			return (1);
		i++;
	}
	return (0);
}

int		is_num(char *string)
{
	int i;

	i = 0;
	if (string[i] == '-')
		i++;
	while (string[i])
	{
		if (!ft_isdigit(string[i]))
			return (0);
		i++;
	}
	return (1);
}

int		full_of_spaces(char *string)
{
	int i;

	i = 0;
	while (string[i])
	{
		if (!is_spaces(string[i]))
			return (string[i] == COMMENT_CHAR ? 1 : 0);
		i++;
	}
	return (1);
}

int		starts_with_end_spaces(char *string, char *start)
{
	int	i;
	int	k;

	i = 0;
	while (is_spaces(string[i]))
		i++;
	k = 0;
	while (string[i + k] && start[k])
	{
		if (start[k] != string[i + k])
			return (0);
		k++;
	}
	if (start[k] || ((string[i + k] && !is_spaces(string[i + k])
	&& string[i + k] != DIRECT_CHAR)))
		return (0);
	return (i + k);
}

int		starts_with(char *string, char *start)
{
	int	i;
	int	k;

	i = 0;
	while (is_spaces(string[i]))
		i++;
	k = 0;
	while (string[i + k] && start[k])
	{
		if (start[k] != string[i + k])
			return (0);
		k++;
	}
	if (start[k])
		return (0);
	return (i + k);
}
