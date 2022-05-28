/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virt_m.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 13:01:32 by msnow-be          #+#    #+#             */
/*   Updated: 2019/03/22 15:56:30 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRT_M_H
# define VIRT_M_H

# define BUF_SIZE	4

# include "op.h"
# include "libft.h"
# include <fcntl.h>
# include <ncurses.h>
# include <time.h>
# include <stdlib.h>

typedef struct			s_champ
{
	int				player_num;
	_Bool			num_auto_assigned;
	char			bot_name[PROG_NAME_LENGTH + 1];
	char			bot_comment[COMMENT_LENGTH + 1];
	int				bot_size;
	unsigned char	*bot_code;
}						t_champ;

typedef struct			s_war
{
	unsigned char	memory[MEM_SIZE];
	int				num_players;
	unsigned char	last_alive_id;
	int				cycles_passed;
	int				num_live_ops;
	int				cycles_to_die;
	int				num_checks;
	int				num_checks_since_last_ctd_change;
	int				next_check;
	int				max_carname;
	char			**quotes;
	t_list			*cars;
}						t_war;

typedef struct			s_debug_mode
{
	int				dump;
	_Bool			show_lives;
	_Bool			show_deaths;
	_Bool			show_cycles;
	_Bool			show_ops;
	_Bool			visualize;
	_Bool			show_aff;
}						t_debug_mode;

typedef struct			s_car
{
	int				id;
	_Bool			carry;
	unsigned char	op_code;
	int				last_alive_time;
	int				cycles_until_action;
	int				position;
	int				bytes_to_next_op;
	int				reg[REG_NUMBER];
	int				player_id;
	int				args[3];
	unsigned char	arg_codes[3];
	int				num_args;
	_Bool			op_success;
}						t_car;

extern t_op				g_op_tab[17];
void					print_ncurses1(t_war *war, t_list *champions, int i,
							int isend);
void					print_champ(t_list *champions, int i, int x, int y);
char					*find_name(int i, t_list *champions);
int						print_char(int k, int len, int y, char c);
void					print_name(t_champ *ch, int k, int y, int y1);
void					print_norm_name(t_champ *ch, int k, int y, int y1);
void					print_comment(int k, int y, t_champ *ch, int y1);
void					print_short_comment(int k, int y, char *ch, int y1);
void					print_imeg(int count, int y, int k);
int						len_list(t_list *champions);
int						is_end(int cars[4]);
int						chat_num(t_war *war, t_list *champions, int i, int m);
int						count_car(t_list *car, int cars[4], int max);
void					init_ncurse(t_war *war, t_list *champions);
_Bool					attach_car_to_list(t_car *car, t_list **cars_list);
_Bool					attach_champ(t_champ *champ, t_list **champs_list,
							_Bool *error_shown);
void					check(t_war *war, t_list **cars, t_debug_mode *debug);
void					clean_all(t_war *war, t_list **champions,
							t_debug_mode **debug);
void					clear_champions(t_list **champions);
void					corewar(t_war *war, t_list *champions,
							t_debug_mode *debug);
void					del_car(void *content, size_t size);
void					fill_arg_codes(t_car *car, unsigned char codage,
							int num_args);
void					fill_memory_with_value(t_war *war, int pos,
							unsigned int value);
t_champ					*find_champion(t_list *champions, unsigned char id);
unsigned char			first_bits(unsigned char ch);
void					ft_lstdel_nocpy(t_list **alst);
t_list					*ft_lstnew_nocpy(void const *content,
							size_t content_size);
void					ft_lst_push_back(t_list *lst1, t_list *lst2);
int						get_bytes_to_skip(unsigned char codage, char num_args,
							char dir_size);
t_debug_mode			*get_debug_mode(char **argv, int *arg_i);
_Bool					get_next_champion(char **argv, int *i,
							t_list **champions);
int						get_new_id(t_list *cars);
int						get_pos(int initial_pos);
t_list					*initialize_cars(t_list *championst, t_war *war);
t_war					initialize_corewar(t_list *champions);
void					introduce_champions(t_list *champs);
void					load_num_into_reg(t_car *car, int reg, int num);
int						lst_len(t_list *lst);
unsigned int			parse_bits(unsigned char *memory, int start,
							int num_bits);
void					perform_actions(t_war *war, t_list *champions,
							t_debug_mode *debug);
void					perform_aff(t_war *war, t_car *car,
							t_debug_mode *debug);
void					perform_arithmetics(t_war *war, t_car *car);
void					perform_bitwise(t_war *war, t_car *car);
_Bool					perform_fork(t_war *war, t_car *car);
void					perform_load(t_war *war, t_car *car);
void					perform_load_store_index(t_war *war, t_car *car);
void					perform_store(t_war *war, t_car *car);
void					perform_zjmp(t_war *war, t_car *car);
void					print_dump_memory(const void *addr);
void					print_memory(const void *addr, int start, size_t size);
_Bool					read_champ(t_champ *champ, int fd, char *filename,
							_Bool *error_shown);
unsigned char			second_bits(unsigned char ch);
unsigned char			third_bits(unsigned char ch);

#endif
