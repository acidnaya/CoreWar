/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_load.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:57:14 by msnow-be          #+#    #+#             */
/*   Updated: 2019/03/19 16:22:27 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virt_m.h"
#include "op.h"

static _Bool	load_codes_ok(unsigned char *codes)
{
	if ((codes[0] == DIR_CODE || codes[0] == IND_CODE)
		&& codes[1] == REG_CODE)
		return (1);
	else
		return (0);
}

/*
** Corewar machine given to us by 42 is terribly strange and reads 2 bits
** instead of 4 on long load.
*/

static int		parse_number_for_load(t_war *war, t_car *car, short skip)
{
	int number;

	if (car->op_code == 2)
		number = parse_bits(war->memory, car->position + skip, 4);
	else
		number = (short)parse_bits(war->memory, car->position + skip, 2);
	return (number);
}

static int		get_first_arg_for_ind(t_war *war, t_car *car)
{
	int result;

	result = (short)parse_bits(war->memory, car->position + 2, IND_SIZE);
	return (result);
}

/*
** Loads a num from memory to a car register.
*/

void			perform_load(t_war *war, t_car *car)
{
	unsigned char	codage;
	int				number;
	short			skip;

	codage = parse_bits(war->memory, car->position + 1, 1);
	fill_arg_codes(car, codage, 2);
	car->bytes_to_next_op = get_bytes_to_skip(codage, 2, 4);
	if (load_codes_ok(car->arg_codes))
	{
		if (car->arg_codes[0] == DIR_CODE)
		{
			car->args[0] = parse_bits(war->memory, car->position + 2, 4);
			car->args[1] = parse_bits(war->memory, car->position + 6, 1);
			number = car->args[0];
		}
		else
		{
			car->args[0] = get_first_arg_for_ind(war, car);
			skip = (car->op_code == 2 ? car->args[0] % IDX_MOD : car->args[0]);
			number = parse_number_for_load(war, car, skip);
			car->args[1] = parse_bits(war->memory, car->position + 4, 1);
		}
		if (car->args[1] > 0 && car->args[1] <= REG_NUMBER)
			load_num_into_reg(car, car->args[1], number);
	}
}
