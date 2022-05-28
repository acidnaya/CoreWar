/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 13:10:26 by msnow-be          #+#    #+#             */
/*   Updated: 2019/03/14 16:20:52 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "virt_m.h"
#include "libft.h"
#include "op.h"

t_champ	*initialize_new_champion(void)
{
	t_champ		*champ;

	if (!(champ = (t_champ *)malloc(sizeof(t_champ))))
		return (NULL);
	champ->player_num = -1;
	champ->num_auto_assigned = 1;
	ft_bzero(champ->bot_name, sizeof(champ->bot_name));
	champ->bot_size = -1;
	ft_bzero(champ->bot_comment, sizeof(champ->bot_comment));
	champ->bot_code = NULL;
	return (champ);
}

void	record_player_num(t_champ *champ, char **argv, int *arg_num)
{
	char	*arg;
	_Bool	is_numeric;

	is_numeric = 1;
	arg = argv[*arg_num + 1];
	while (*arg)
	{
		if (*arg < '0' || *arg > '9')
		{
			is_numeric = 0;
			break ;
		}
		arg++;
	}
	champ->player_num = (is_numeric ? ft_atoi(argv[*arg_num + 1]) : 0);
	champ->num_auto_assigned = 0;
	*arg_num += 2;
}

_Bool	get_next_champion(char **argv, int *arg_num, t_list **champions)
{
	t_champ		*champ;
	int			fd;
	_Bool		error_shown;

	if (!(champ = initialize_new_champion()))
		return (0);
	if (!ft_strncmp(argv[*arg_num], "-n\0", 3))
		record_player_num(champ, argv, arg_num);
	if ((fd = open(argv[*arg_num], 'r')) < 0)
	{
		ft_printf("Can't read source file %s\n", argv[*arg_num]);
		free(champ);
		return (0);
	}
	error_shown = 0;
	if (fd > 0 && (!read_champ(champ, fd, argv[*arg_num], &error_shown)
		|| !attach_champ(champ, champions, &error_shown)))
	{
		error_shown ? 1 : ft_putendl("Error parsing champion");
		free(champ);
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
