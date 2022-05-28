/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_cars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 17:19:29 by msnow-be          #+#    #+#             */
/*   Updated: 2019/03/21 15:52:01 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virt_m.h"
#include "libft.h"

t_car	*init_car(t_champ *champ, int num_players, t_war *war)
{
	t_car	*result;

	if (!(result = (t_car *)malloc(sizeof(t_car))))
	{
		ft_putendl("Memory allocation error.\n");
		return (NULL);
	}
	result->id = war->max_carname + 1;
	war->max_carname++;
	result->carry = 0;
	result->op_code = -1;
	result->last_alive_time = 0;
	result->cycles_until_action = 0;
	result->position = MEM_SIZE / num_players * (champ->player_num - 1);
	result->bytes_to_next_op = -1;
	ft_bzero(result->reg, sizeof(result->reg));
	result->reg[0] = champ->player_num * -1;
	result->player_id = champ->player_num;
	ft_bzero(result->args, sizeof(result->args));
	result->num_args = 0;
	result->op_success = 0;
	return (result);
}

_Bool	attach_car_to_list(t_car *car, t_list **cars_list)
{
	t_list	*lst;

	if (!(lst = ft_lstnew_nocpy(car, sizeof(t_car *))))
	{
		ft_putendl("Memory allocation error.\n");
		return (0);
	}
	if (!(*cars_list))
		*cars_list = lst;
	else
		ft_lstadd(cars_list, lst);
	return (1);
}

t_list	*initialize_cars(t_list *champions, t_war *war)
{
	t_champ		*champ;
	t_car		*current_car;
	t_list		*cars;
	int			num_players;

	cars = NULL;
	num_players = lst_len(champions);
	while (champions)
	{
		champ = (t_champ *)champions->content;
		if (!(current_car = init_car(champ, num_players, war)))
		{
			ft_lstdel(&cars, del_car);
			return (NULL);
		}
		if (!(attach_car_to_list(current_car, &cars)))
		{
			ft_lstdel(&cars, del_car);
			return (NULL);
		}
		champions = champions->next;
	}
	return (cars);
}
