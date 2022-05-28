/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bitwise.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 18:47:08 by msnow-be          #+#    #+#             */
/*   Updated: 2019/03/21 16:56:19 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virt_m.h"
#include "op.h"

static _Bool	bitwise_codes_ok(unsigned char *codes)
{
	if (codes[0] && codes[1] && codes[2] == REG_CODE)
		return (1);
	else
		return (0);
}

/*
** Check whether we need to use a register number or a value from a register
*/

static int		get_reg_arg_val(t_car *car, int arg_num, int parsed_num)
{
	if (arg_num == 2)
		return (parsed_num);
	else
		return (car->reg[parsed_num - 1]);
}

/*
** Reads a number from memory in place or reads in from some other place
*/

static int		get_d_i_arg_val(t_car *car, t_war *war,
	unsigned char argcode, int parsed_num)
{
	if (argcode == DIR_CODE)
		return (parsed_num);
	else
		return (parse_bits(war->memory, car->position + (short)parsed_num,
			4));
}

_Bool			collect_args_bw(t_war *war, t_car *car, int *args,
	unsigned char *argcodes)
{
	int				off;
	int				i;
	int				parse_size;

	off = 2;
	i = -1;
	while (++i < 3)
	{
		if (argcodes[i] == REG_CODE)
		{
			car->args[i] = parse_bits(war->memory, car->position + off, 1);
			if (car->args[i] <= 0 || car->args[i] > REG_NUMBER)
				return (0);
			*(args + i) = get_reg_arg_val(car, i, car->args[i]);
		}
		else
		{
			parse_size = (argcodes[i] == DIR_CODE ? 4 : 2);
			car->args[i] = parse_bits(war->memory, car->position + off,
				parse_size);
			*(args + i) = get_d_i_arg_val(car, war, argcodes[i], car->args[i]);
		}
		off += (argcodes[i] == REG_CODE ? 1 : parse_size);
	}
	return (1);
}

/*
** Collects two first args and writes the result of a bitwise opertion
** to the register given as a third argument
*/

void			perform_bitwise(t_war *war, t_car *car)
{
	unsigned char	codage;
	int				args[3];

	codage = parse_bits(war->memory, car->position + 1, 1);
	fill_arg_codes(car, codage, 3);
	car->bytes_to_next_op = get_bytes_to_skip(codage, 3, 4);
	if (bitwise_codes_ok(car->arg_codes))
	{
		if (collect_args_bw(war, car, args, car->arg_codes))
		{
			if (car->op_code == 6)
				car->reg[car->args[2] - 1] = args[0] & args[1];
			else if (car->op_code == 7)
				car->reg[car->args[2] - 1] = args[0] | args[1];
			else if (car->op_code == 8)
				car->reg[car->args[2] - 1] = args[0] ^ args[1];
			car->carry = (car->reg[args[2] - 1] ? 0 : 1);
			car->op_success = 1;
		}
	}
}
