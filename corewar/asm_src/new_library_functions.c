/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_library_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfriesen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:06:48 by jfriesen          #+#    #+#             */
/*   Updated: 2019/02/15 15:06:50 by jfriesen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include "libft.h"

int		starts_with_command(char *string)
{
	if (starts_with_end_spaces(string, "sub") ||
	starts_with_end_spaces(string, "ld") ||
	starts_with_end_spaces(string, "add") ||
	starts_with_end_spaces(string, "st") ||
	starts_with_end_spaces(string, "and") ||
	starts_with_end_spaces(string, "or") ||
	starts_with_end_spaces(string, "xor") ||
	starts_with_end_spaces(string, "zjmp") ||
	starts_with_end_spaces(string, "ldi") ||
	starts_with_end_spaces(string, "fork") ||
	starts_with_end_spaces(string, "lld") ||
	starts_with_end_spaces(string, "live") ||
	starts_with_end_spaces(string, "aff") ||
	starts_with_end_spaces(string, "lldi") ||
	starts_with_end_spaces(string, "sti") ||
	starts_with_end_spaces(string, "lfork"))
		return (1);
	return (0);
}

int		command_type1(char *string)
{
	if (starts_with_end_spaces(string, "live"))
		return (1);
	else if (starts_with_end_spaces(string, "ld"))
		return (2);
	else if (starts_with_end_spaces(string, "st"))
		return (3);
	else if (starts_with_end_spaces(string, "add"))
		return (4);
	else if (starts_with_end_spaces(string, "sub"))
		return (5);
	else if (starts_with_end_spaces(string, "and"))
		return (6);
	else if (starts_with_end_spaces(string, "or"))
		return (7);
	else if (starts_with_end_spaces(string, "xor"))
		return (8);
	return (0);
}

int		command_type2(char *string)
{
	if (starts_with_end_spaces(string, "zjmp"))
		return (9);
	else if (starts_with_end_spaces(string, "ldi"))
		return (10);
	else if (starts_with_end_spaces(string, "sti"))
		return (11);
	else if (starts_with_end_spaces(string, "lfork"))
		return (15);
	else if (starts_with_end_spaces(string, "lldi"))
		return (14);
	else if (starts_with_end_spaces(string, "fork"))
		return (12);
	else if (starts_with_end_spaces(string, "lld"))
		return (13);
	else if (starts_with_end_spaces(string, "aff"))
		return (16);
	return (0);
}

int		command_type(char *s)
{
	int	k;

	k = command_type2(s);
	if (k)
		return (k);
	k = command_type1(s);
	return (k);
}

int		put_space_before_direct_char(char **line)
{
	int		i;
	char	*first;
	char	*second;

	i = 0;
	while ((*line)[i] && (*line)[i] != DIRECT_CHAR)
		i++;
	if (i >= (int)ft_strlen(*line) || (i > 0 && is_spaces((*line)[i - 1])))
		return (1);
	first = ft_strsub(*line, 0, i);
	second = ft_strdup(&((*line)[i]));
	free(*line);
	*line = ft_strjoin(first, " ");
	free(first);
	first = ft_strjoin(*line, second);
	free(*line);
	free(second);
	*line = first;
	return (1);
}
