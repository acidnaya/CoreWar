/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:18:05 by msnow-be          #+#    #+#             */
/*   Updated: 2019/03/13 13:22:32 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "virt_m.h"
#include "op.h"

/*
** Finds how many bytes the operation takes.
*/

int			get_bytes_to_skip(unsigned char codage, char num_args,
	char dir_size)
{
	unsigned char	arg_sizes[3];
	int				i;
	int				result;

	arg_sizes[0] = first_bits(codage);
	arg_sizes[1] = second_bits(codage);
	arg_sizes[2] = third_bits(codage);
	i = 0;
	result = 2;
	while (i < num_args)
	{
		if (arg_sizes[i] == DIR_CODE)
			result += dir_size;
		else if (arg_sizes[i] == REG_CODE)
			result += 1;
		else if (arg_sizes[i] == IND_CODE)
			result += 2;
		i++;
	}
	return (result);
}

void		perform_live(t_war *war, t_car *car, t_list *champions,
	t_debug_mode *debug)
{
	short			player_number;
	t_champ			*champ;

	player_number = parse_bits(war->memory, car->position + 1, 4) * -1;
	car->args[0] = player_number;
	car->num_args = 1;
	car->arg_codes[0] = DIR_CODE;
	car->bytes_to_next_op = 5;
	car->last_alive_time = war->cycles_passed;
	war->num_live_ops++;
	car->op_success = 1;
	if (player_number > 0 && player_number <= war->num_players)
	{
		war->last_alive_id = player_number;
		champ = find_champion(champions, player_number);
		if (debug->show_lives)
			ft_printf("Player %d (%s) is said to be alive)\n", player_number,
				champ->bot_name);
	}
}

void		make_current_action(t_war *war, t_car *car, t_list *champions,
	t_debug_mode *debug)
{
	car->op_success = 0;
	if (car->op_code == 1)
		perform_live(war, car, champions, debug);
	else if (car->op_code == 2 || car->op_code == 13)
		perform_load(war, car);
	else if (car->op_code == 3)
		perform_store(war, car);
	else if (car->op_code == 4 || car->op_code == 5)
		perform_arithmetics(war, car);
	else if (car->op_code == 6 || car->op_code == 7 || car->op_code == 8)
		perform_bitwise(war, car);
	else if (car->op_code == 9)
		perform_zjmp(war, car);
	else if (car->op_code == 10 || car->op_code == 14 || car->op_code == 11)
		perform_load_store_index(war, car);
	else if (car->op_code == 12 || car->op_code == 15)
	{
		if (!(perform_fork(war, car)))
		{
			clean_all(war, &champions, &debug);
			exit(0);
		}
	}
	else if (car->op_code == 16)
		perform_aff(war, car, debug);
}

void		show_operation(t_car *car)
{
	int	i;

	i = 0;
	if (car->op_success)
	{
		ft_printf("Process %d\tperforms %s\t", car->id,
			g_op_tab[car->op_code - 1].name);
		while (i < car->num_args)
		{
			if (car->arg_codes[i] == IND_CODE)
				ft_putstr("i ");
			else if (car->arg_codes[i] == DIR_CODE)
				ft_putstr("d ");
			else if (car->arg_codes[i] == REG_CODE)
				ft_putchar('r');
			ft_printf("%d\t", car->args[i]);
			if (car->op_code == 9)
				car->carry ? ft_putstr("Success") : ft_putstr("Fail");
			i++;
		}
		ft_putchar('\n');
	}
}

/*
** Runs through all the cars and detects and performs actions.
*/

void		perform_actions(t_war *war, t_list *champions,
	t_debug_mode *debug)
{
	t_car	*car;
	t_list	*ptr;

	ptr = war->cars;
	while (ptr)
	{
		car = (t_car *)ptr->content;
		if (car->cycles_until_action <= 0)
		{
			car->op_code = war->memory[car->position];
			if (car->op_code >= 0x01 && car->op_code <= 0x10)
				car->cycles_until_action = g_op_tab[car->op_code - 1].wait;
			else
				car->bytes_to_next_op = 1;
		}
		if (--car->cycles_until_action <= 0)
		{
			if (car->op_code >= 0x01 && car->op_code <= 0x10)
				make_current_action(war, car, champions, debug);
			if (car->op_code >= 0x01 && car->op_code <= 0x10 && debug->show_ops)
				show_operation(car);
			car->position = get_pos(car->position + car->bytes_to_next_op);
		}
		ptr = ptr->next;
	}
}
