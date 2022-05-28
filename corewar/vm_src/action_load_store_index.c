/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_load_store_index.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 16:00:37 by msnow-be          #+#    #+#             */
/*   Updated: 2019/03/20 19:14:28 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "virt_m.h"
#include "op.h"

static _Bool	load_store_index_codes_ok(unsigned char op_code,
	unsigned char *codes)
{
	if (((op_code == 10 || op_code == 14) && codes[0] &&
		(codes[1] == REG_CODE || codes[1] == DIR_CODE) &&
		codes[2] == REG_CODE) ||
		(op_code == 11 &&
		codes[0] == REG_CODE && codes[1] &&
		(codes[2] == REG_CODE || codes[2] == DIR_CODE)))
		return (1);
	else
		return (0);
}

/*
** Check whether we need to use a register number or a value from a register
*/

static int		get_reg_arg_value(t_car *car, int arg_num, int parsed_num)
{
	if ((car->op_code == 10 || car->op_code == 14) && arg_num == 2)
		return (parsed_num);
	else
		return (car->reg[parsed_num - 1]);
}

/*
** Reads a number from memory in place or reads in from some other place
*/

static int		get_dir_ind_arg_value(t_car *car, t_war *war,
	unsigned char argcode, short parsed_num)
{
	if (argcode == DIR_CODE)
		return (parsed_num);
	else
		return (parse_bits(war->memory, car->position + parsed_num, 4));
}

_Bool			collect_args_ldsi(t_war *war, t_car *car, int *args,
	unsigned char *argcodes)
{
	int				offset;
	int				i;

	offset = 2;
	i = -1;
	while (++i < 3)
	{
		if (argcodes[i] == REG_CODE)
		{
			car->args[i] = parse_bits(war->memory, car->position + offset, 1);
			if (car->args[i] <= 0 || car->args[i] > REG_NUMBER)
				return (0);
			*(args + i) = get_reg_arg_value(car, i, car->args[i]);
			offset += 1;
		}
		else
		{
			car->args[i] = (short)parse_bits(war->memory,
				car->position + offset, 2);
			*(args + i) = get_dir_ind_arg_value(car, war, argcodes[i],
				car->args[i]);
			offset += 2;
		}
	}
	return (1);
}

/*
** Reads args and reads or writes between car registers and memory.
** It's not really obvious, but regardless of the fact that DIR_SIZE
** for this function is 2 (meaning argumants are parsed as shorts),
** when we read and write numbers, we use 4-byte-sized ints.
*/

void			perform_load_store_index(t_war *war, t_car *car)
{
	unsigned char	codage;
	int				args[3];
	int				skip;

	codage = parse_bits(war->memory, car->position + 1, 1);
	car->bytes_to_next_op = get_bytes_to_skip(codage, 3, 2);
	fill_arg_codes(car, codage, 3);
	if (load_store_index_codes_ok(car->op_code, car->arg_codes))
	{
		if (collect_args_ldsi(war, car, args, car->arg_codes))
		{
			skip = (car->op_code != 11 ? args[0] + args[1] : args[1] + args[2]);
			skip = (car->op_code != 14 ? skip % IDX_MOD : skip);
			if (car->op_code == 10 || car->op_code == 14)
				load_num_into_reg(car, args[2], parse_bits(war->memory,
					car->position + skip, 4));
			else if (car->op_code == 11)
			{
				fill_memory_with_value(war, car->position + skip, args[0]);
				car->op_success = 1;
			}
		}
	}
}
