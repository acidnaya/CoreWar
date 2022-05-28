/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 15:14:29 by msnow-be          #+#    #+#             */
/*   Updated: 2019/03/05 13:20:57 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "virt_m.h"

static void	delete_car(t_car **car, t_list *prev, t_list *next, t_list **cars)
{
	free(*car);
	*car = NULL;
	if (prev)
		prev->next = next;
	else
		*cars = next;
}

void		delete_dead_cars(t_list **cars, int cycles_passed,
	int cycles_to_die, t_debug_mode *debug)
{
	t_list	*ptr;
	t_car	*car;
	t_list	*prev;
	t_list	*next;

	prev = NULL;
	ptr = *cars;
	while (ptr)
	{
		car = (t_car *)ptr->content;
		next = ptr->next;
		if (cycles_passed - car->last_alive_time >= cycles_to_die)
		{
			if (debug->show_deaths)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
					car->id, cycles_passed - car->last_alive_time,
					cycles_to_die);
			delete_car(&car, prev, next, cars);
			free(ptr);
		}
		else
			prev = ptr;
		ptr = next;
	}
}

/*
** Deletes dead cars and checks if we need to decrease cycles_to_die value
*/

void		check(t_war *war, t_list **cars, t_debug_mode *debug)
{
	war->num_checks += 1;
	delete_dead_cars(cars, war->cycles_passed, war->cycles_to_die, debug);
	if (war->num_live_ops >= NBR_LIVE ||
		++(war->num_checks_since_last_ctd_change) == MAX_CHECKS)
	{
		war->cycles_to_die -= CYCLE_DELTA;
		war->num_checks_since_last_ctd_change = 0;
	}
	war->num_live_ops = 0;
	war->next_check = war->cycles_passed + war->cycles_to_die;
}
