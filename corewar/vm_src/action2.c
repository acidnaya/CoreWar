/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 14:23:20 by msnow-be          #+#    #+#             */
/*   Updated: 2019/03/21 15:21:37 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "virt_m.h"
#include "op.h"

static void	store_reg_into_memory(t_war *war, t_car *car, int reg_num)
{
	short	skip;

	car->args[1] = (short)parse_bits(war->memory, car->position + 3, IND_SIZE);
	skip = car->args[1] % IDX_MOD;
	fill_memory_with_value(war, car->position + skip, car->reg[reg_num - 1]);
	car->op_success = 1;
}

/*
** Writes the value from the register either to memory adress
** or to another register.
*/

void		perform_store(t_war *war, t_car *car)
{
	unsigned char	codage;

	codage = parse_bits(war->memory, car->position + 1, 1);
	fill_arg_codes(car, codage, 2);
	car->bytes_to_next_op = get_bytes_to_skip(codage, 2, 4);
	if (car->arg_codes[0] == REG_CODE &&
		(car->arg_codes[1] == REG_CODE || car->arg_codes[1] == IND_CODE))
	{
		car->args[0] = parse_bits(war->memory, car->position + 2, 1);
		if (car->args[0] > 0 && car->args[0] <= REG_NUMBER)
		{
			if (car->arg_codes[1] == REG_CODE)
			{
				car->args[1] = parse_bits(war->memory, car->position + 3, 1);
				if (car->args[1] > 0 && car->args[1] <= REG_NUMBER)
				{
					car->reg[car->args[1] - 1] = car->reg[car->args[0] - 1];
					car->op_success = 1;
				}
			}
			else if (car->arg_codes[1] == IND_CODE)
				store_reg_into_memory(war, car, car->args[0]);
		}
	}
}

/*
** Gets three register numbers, performs some atithmetics operation
** on the first two of them and writes the result to the third one.
*/

void		perform_arithmetics(t_war *war, t_car *car)
{
	unsigned char	codage;
	int				result;

	codage = parse_bits(war->memory, car->position + 1, 1);
	fill_arg_codes(car, codage, 3);
	car->bytes_to_next_op = get_bytes_to_skip(codage, 3, 4);
	if (car->arg_codes[0] == REG_CODE && car->arg_codes[1] == REG_CODE
		&& car->arg_codes[2] == REG_CODE)
	{
		car->args[0] = parse_bits(war->memory, car->position + 2, 1);
		car->args[1] = parse_bits(war->memory, car->position + 3, 1);
		car->args[2] = parse_bits(war->memory, car->position + 4, 1);
		if (car->args[0] > 0 && car->args[0] <= REG_NUMBER &&
			car->args[1] > 0 && car->args[1] <= REG_NUMBER &&
			car->args[2] > 0 && car->args[2] <= REG_NUMBER)
		{
			if (car->op_code == 4)
				result = car->reg[car->args[0] - 1] +
					car->reg[car->args[1] - 1];
			else
				result = car->reg[car->args[0] - 1] -
					car->reg[car->args[1] - 1];
			load_num_into_reg(car, car->args[2], result);
		}
	}
}

/*
** Jumps to some place in memory if car->carry flag is true.
*/

void		perform_zjmp(t_war *war, t_car *car)
{
	car->num_args = 1;
	car->arg_codes[0] = DIR_CODE;
	car->bytes_to_next_op = (car->carry ? 0 : 3);
	car->op_success = 1;
	if (car->carry)
	{
		car->args[0] = (short)parse_bits(war->memory, car->position + 1, 2);
		car->position = get_pos(car->position + car->args[0] % IDX_MOD);
	}
}

/*
** Prints registry value as a char to standart output
*/

void		perform_aff(t_war *war, t_car *car, t_debug_mode *debug)
{
	char			ch;
	unsigned char	codage;

	codage = parse_bits(war->memory, car->position + 1, 1);
	car->num_args = 1;
	car->bytes_to_next_op = get_bytes_to_skip(codage, car->num_args, 4);
	car->arg_codes[0] = REG_CODE;
	car->args[0] = parse_bits(war->memory, car->position + 1, 1);
	if (codage == 40 && car->args[0] > 0 && car->args[0] <= REG_NUMBER)
	{
		car->op_success = 1;
		ch = car->reg[car->args[0] - 1];
		if (debug->show_aff)
			ft_putchar(ch);
	}
}
