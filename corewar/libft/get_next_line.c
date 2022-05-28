/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:27:21 by msnow-be          #+#    #+#             */
/*   Updated: 2019/03/14 14:56:01 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

static char	*extract_line(char **text, int *status)
{
	size_t	end;
	char	*str;
	char	*str_end;
	char	*result;

	end = 0;
	str = *text;
	while ((str[end] != '\n') && (str[end] != '\0'))
		end++;
	if (str[end] == '\n')
		*status = 1;
	if (!(result = ft_strsub(str, 0, end)))
		return (NULL);
	if (!(str_end = ft_strsub(str, end + 1, ft_strlen(str) - end)))
	{
		free(result);
		return (NULL);
	}
	free(str);
	*text = str_end;
	return (result);
}

int			get_next_line(const int fd, char **line)
{
	static char	*read_registry[4096];
	char		buf[BUFF_SIZE + 1];
	char		*tmp;
	int			status;

	if (!line || (fd < 0))
		return (-1);
	while ((status = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[status] = '\0';
		if (!read_registry[fd])
			read_registry[fd] = ft_strnew(sizeof(char));
		tmp = ft_strjoin(read_registry[fd], buf);
		free(read_registry[fd]);
		read_registry[fd] = tmp;
		if (ft_strchr(read_registry[fd], '\n'))
			break ;
	}
	if ((status > 0) || (!status && ((read_registry[fd] != (NULL))
		&& (read_registry[fd][0] != '\0'))))
	{
		*line = extract_line(&read_registry[fd], &status);
		status = (!(*line) ? -1 : 1);
	}
	return (status);
}
