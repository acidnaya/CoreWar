/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 13:10:26 by msnow-be          #+#    #+#             */
/*   Updated: 2019/03/22 16:31:23 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virt_m.h"
#include "libft.h"
#include "op.h"

_Bool	check_magic_header(unsigned char *header, _Bool *error_shown)
{
	int magic;

	magic = parse_bits(header, 0, 4);
	if (magic != COREWAR_EXEC_MAGIC)
	{
		ft_putendl("Error: Invalid magic header!");
		*error_shown = 1;
		return (0);
	}
	else
		return (1);
}

/*
** Checks if bot size is ok and adds this value to our chamoion structure
*/

_Bool	process_bot_size(unsigned char *buff, t_champ *champ, char *filename,
	_Bool *error_shown)
{
	int size;

	size = parse_bits(buff, 0, 4);
	champ->bot_size = size;
	if (size > CHAMP_MAX_SIZE)
	{
		ft_printf("Error: File %s has too large code (%d bytes > %d bytes)\n",
			filename, champ->bot_size, CHAMP_MAX_SIZE);
		*error_shown = 1;
		return (0);
	}
	if (size == 0)
	{
		ft_printf("Error: Code size too small (0)\n");
		*error_shown = 1;
		return (0);
	}
	return (1);
}

_Bool	file_is_ended(int fd, char *filename, _Bool *error_shown)
{
	char	buf[1];
	int		r;

	if ((r = read(fd, buf, 1)) > 0)
	{
		ft_printf("Error: File %s has a code size ", filename);
		ft_printf("that differ from what its header says\n");
		*error_shown = 1;
		return (0);
	}
	else
		return (1);
}

/*
** Champion parsing: 1) reading header, 2) reading champion name
**		3) skipping zero, 4) reading champion size, 5) reading comment,
**		6) skipping zero, 7) allocating space for a bot code and readinhg it
**		8) checking if there is something else left in the file
*/

_Bool	read_champ(t_champ *champ, int fd, char *filename, _Bool *error_shown)
{
	unsigned char	buff[BUF_SIZE + 1];
	int				r;

	if ((r = read(fd, buff, 4)) != 4 || !check_magic_header(buff, error_shown))
		return (0);
	if ((r = read(fd, champ->bot_name, PROG_NAME_LENGTH)) != PROG_NAME_LENGTH)
		return (0);
	read(fd, buff, 4);
	if ((r = read(fd, buff, 4) != 4 ||
		!process_bot_size(buff, champ, filename, error_shown)))
		return (0);
	if ((r = read(fd, champ->bot_comment, COMMENT_LENGTH)) != COMMENT_LENGTH)
		return (0);
	read(fd, buff, 4);
	if (!(champ->bot_code = (unsigned char *)malloc(champ->bot_size)))
	{
		ft_putendl("Memory allocation error");
		return (0);
	}
	if ((r = read(fd, champ->bot_code, champ->bot_size)) != champ->bot_size)
		return (0);
	if (!file_is_ended(fd, filename, error_shown))
		return (0);
	return (1);
}
