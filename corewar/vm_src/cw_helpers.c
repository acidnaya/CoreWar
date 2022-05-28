/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 15:52:02 by msnow-be          #+#    #+#             */
/*   Updated: 2019/03/18 19:10:45 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virt_m.h"
#include "op.h"

/*
** Reads an int from memory
*/

unsigned int	parse_bits(unsigned char *memory, int start, int num_bytes)
{
	unsigned int	result;
	int				i;

	result = 0;
	i = 0;
	while (i < num_bytes)
	{
		result *= 16 * 16;
		result += memory[get_pos(start + i)];
		i++;
	}
	return (result);
}

/*
** Gets a correct adress in a cycled memory
*/

int				get_pos(int initial_pos)
{
	while (initial_pos < 0)
		initial_pos += MEM_SIZE;
	return (initial_pos % MEM_SIZE);
}

/*
** Loads a number into car register and amends carry if the operation
** allows to amend carry. Not all operations that write numbers into
** registers can do that!
*/

void			load_num_into_reg(t_car *car, int reg, int num)
{
	car->reg[reg - 1] = num;
	if (car->op_code == 2 || (car->op_code >= 4 && car->op_code <= 8) ||
		car->op_code == 13 || car->op_code == 14)
		car->carry = (num ? 0 : 1);
	car->op_success = 1;
}

/*
** Writes an integer to a memory
*/

void			fill_memory_with_value(t_war *war, int pos, unsigned int value)
{
	int	i;

	i = 3;
	while (i >= 0)
	{
		war->memory[get_pos(pos + i)] = value & 0b11111111;
		value = value >> 8;
		i--;
	}
}

void			fill_arg_codes(t_car *car, unsigned char codage, int num_args)
{
	car->arg_codes[0] = first_bits(codage);
	car->arg_codes[1] = second_bits(codage);
	car->arg_codes[2] = third_bits(codage);
	car->num_args = num_args;
}
