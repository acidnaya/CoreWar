/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfriesen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:34:17 by jfriesen          #+#    #+#             */
/*   Updated: 2019/03/20 13:34:19 by jfriesen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include "libft.h"

int		starts_with_label(char *string)
{
	int	i;

	i = 0;
	while (is_spaces(string[i]))
		i++;
	while (ft_count_chr(LABEL_CHARS, string[i]) > 0)
		i++;
	if (string[i] == LABEL_CHAR)
		return (i);
	return (0);
}

void	delete_spaces_from_start(char **string)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	while (is_spaces((*string)[i]))
		i++;
	if (i > 0)
	{
		len = ft_strlen(*string);
		new = ft_strsub(*string, i, len - i);
		if (new)
		{
			free(*string);
			*string = new;
		}
	}
}

void	delete_first_word(char **string)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	while (!is_spaces((*string)[i]))
		i++;
	if (i > 0)
	{
		len = ft_strlen(*string);
		new = ft_strsub(*string, i, len - i);
		if (new)
		{
			free(*string);
			*string = new;
		}
	}
}

char	*clean_string(char **string)
{
	if (string && *string)
	{
		free(*string);
		*string = NULL;
	}
	return (NULL);
}

void	clean_array(char ***a)
{
	char	**ptr;
	int		i;

	i = 0;
	ptr = *a;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(*a);
	*a = NULL;
}
