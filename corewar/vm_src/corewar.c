/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 16:38:42 by msnow-be          #+#    #+#             */
/*   Updated: 2019/03/14 15:00:08 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "virt_m.h"

t_champ			*find_champion(t_list *champions, unsigned char id)
{
	t_champ *current_champ;

	while (champions)
	{
		current_champ = (t_champ *)champions->content;
		if (current_champ->player_num == id)
			return (current_champ);
		champions = champions->next;
	}
	return (NULL);
}

static _Bool	run_cycle(t_war *war, t_list *champions, t_debug_mode *debug)
{
	if (debug->show_cycles)
		ft_printf("It is now cycle %d\n", war->cycles_passed);
	perform_actions(war, champions, debug);
	if (war->cycles_to_die <= 0 || war->cycles_passed == war->next_check)
		check(war, &(war->cars), debug);
	war->cycles_passed++;
	if (debug->dump == war->cycles_passed - 1)
	{
		print_dump_memory(war->memory);
		return (0);
	}
	return (1);
}

void			corewar(t_war *war, t_list *champions, t_debug_mode *debug)
{
	t_champ		*winner;

	introduce_champions(champions);
	war->quotes = (char **)ft_memalloc(6 * sizeof(char *));
	if (debug->visualize)
		init_ncurse(war, champions);
	while (war->cars)
	{
		if (debug->visualize)
			print_ncurses1(war, champions, -1, 0);
		if (!(run_cycle(war, champions, debug)))
			return ;
	}
	if (debug->visualize)
	{
		print_ncurses1(war, champions, -1, 1);
		endwin();
	}
	winner = find_champion(champions, war->last_alive_id);
	ft_printf("Contestant %d, \"%s\", has won !\n",
		winner->player_num, winner->bot_name);
}
