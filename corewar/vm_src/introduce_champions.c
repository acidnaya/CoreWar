/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   introduce_champions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:49:44 by msnow-be          #+#    #+#             */
/*   Updated: 2019/02/27 15:05:56 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virt_m.h"
#include "libft.h"
#include "ft_printf.h"

void	introduce_champions(t_list *champs)
{
	t_champ	*ch;

	ft_printf("Introducing contestants...\n");
	while (champs)
	{
		ch = (t_champ *)champs->content;
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			ch->player_num, ch->bot_size, ch->bot_name, ch->bot_comment);
		champs = champs->next;
	}
}
