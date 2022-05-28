/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_corewar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:56:58 by msnow-be          #+#    #+#             */
/*   Updated: 2019/02/28 15:43:28 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virt_m.h"

void	add_players_code(unsigned char *memory, int num_players,
	t_list *champions)
{
	int		i;
	int		start;
	t_champ	*champ;

	i = 0;
	while (i < num_players)
	{
		champ = (t_champ *)champions->content;
		start = MEM_SIZE / num_players * (champ->player_num - 1);
		ft_memcpy(memory + start, champ->bot_code, champ->bot_size);
		champions = champions->next;
		i++;
	}
}

t_war	initialize_corewar(t_list *champions)
{
	t_war	war;

	ft_bzero(war.memory, sizeof(war.memory));
	war.num_players = lst_len(champions);
	war.last_alive_id = lst_len(champions);
	war.cycles_passed = 1;
	war.num_live_ops = 0;
	war.cycles_to_die = CYCLE_TO_DIE;
	war.num_checks = 0;
	war.num_checks_since_last_ctd_change = 0;
	war.next_check = CYCLE_TO_DIE;
	war.max_carname = 0;
	add_players_code(war.memory, war.num_players, champions);
	war.cars = NULL;
	return (war);
}
