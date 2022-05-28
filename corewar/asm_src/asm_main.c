/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfriesen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:35:55 by jfriesen          #+#    #+#             */
/*   Updated: 2019/03/19 18:35:58 by jfriesen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

char		*new_filename(char *filename)
{
	int		i;
	int		len;
	char	*new;

	i = -1;
	len = ft_strlen(filename);
	if (filename[len - 1] != 's' || filename[len - 2] != '.')
		return (filename);
	if (!(new = (char *)malloc((len + 3) * sizeof(char))))
		return (NULL);
	ft_bzero(new, len + 3);
	while (++i < len - 1)
		new[i] = filename[i];
	new[len - 1] = 'c';
	new[len] = 'o';
	new[len + 1] = 'r';
	return (new);
}

t_info		*get_byte_code(int fd)
{
	t_info	*info;

	info = NULL;
	info = lexical_analyzer(fd);
	if (!info->operations)
		error_exit("Code was not found", 0, NULL, &info);
	return (info);
}

int			main(int argc, char **argv)
{
	char	*new;
	t_info	*info;
	int		fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		new = new_filename(argv[1]);
		if (!new)
			write(2, "An error has occured during programm execution.\n", 48);
		else if (!ft_strcmp(new, argv[1]) || fd == -1)
			write(2, "Argument is incorrect.\n", 23);
		else
		{
			info = get_byte_code(fd);
			close(fd);
			put_byte_code_into_newfile(new, info);
		}
	}
	else
		write(2, "Wrong number of arguments.\n", 27);
	return (0);
}
