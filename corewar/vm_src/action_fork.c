/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 16:15:17 by msnow-be          #+#    #+#             */
/*   Updated: 2019/03/05 15:46:49 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "virt_m.h"
#include "op.h"

static _Bool	copy_car(t_car *car, t_list **cars, short skip, t_war *war)
{
	t_car	*copy;
	int		i;

	if (!(copy = (t_car *)malloc(sizeof(t_car))))
	{
		ft_putendl("Memory allocation error");
		return (0);
	}
	copy->id = war->max_carname + 1;
	war->max_carname++;
	copy->carry = car->carry;
	copy->op_code = car->op_code;
	copy->last_alive_time = car->last_alive_time;
	copy->cycles_until_action = 0;
	copy->position = get_pos(car->position + skip);
	copy->bytes_to_next_op = 0;
	i = 0;
	while (i < REG_NUMBER)
	{
		copy->reg[i] = car->reg[i];
		i++;
	}
	copy->player_id = car->player_id;
	attach_car_to_list(copy, cars);
	return (1);
}

_Bool			perform_fork(t_war *war, t_car *car)
{
	short	skip;

	car->num_args = 1;
	car->arg_codes[0] = DIR_CODE;
	car->bytes_to_next_op = 3;
	car->args[0] = (short)parse_bits(war->memory, car->position + 1, 2);
	skip = (car->op_code == 12 ? car->args[0] % IDX_MOD : car->args[0]);
	if (!(copy_car(car, &(war->cars), skip, war)))
		return (0);
	car->op_success = 1;
	return (1);
}
