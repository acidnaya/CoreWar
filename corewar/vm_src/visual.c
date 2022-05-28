/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraynor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 20:27:37 by mraynor           #+#    #+#             */
/*   Updated: 2019/03/05 20:27:40 by mraynor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virt_m.h"

void	init_ncurse(t_war *war, t_list *champions)
{
	srand(time(NULL));
	initscr();
	cbreak();
	noecho();
	start_color();
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_CYAN);
	init_pair(3, COLOR_BLACK, COLOR_YELLOW);
	init_pair(4, COLOR_WHITE, COLOR_BLUE);
	init_pair(5, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(6, COLOR_BLACK, COLOR_GREEN);
	init_pair(8, COLOR_YELLOW, COLOR_BLACK);
	init_pair(9, COLOR_BLUE, COLOR_BLACK);
	init_pair(10, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(11, COLOR_GREEN, COLOR_BLACK);
	init_pair(14, COLOR_YELLOW, COLOR_BLACK);
	init_pair(12, COLOR_WHITE, COLOR_CYAN);
	init_pair(13, COLOR_RED, COLOR_BLACK);
	init_color(COLOR_CYAN, 599, 0, 0);
	print_champ(champions, 0, 0, 0);
	getch();
	doupdate();
}

int		find_car(int i, t_list *car)
{
	t_car *t;

	if (!car)
		return (-1);
	t = (t_car *)car->content;
	if (i == t->position)
		return (t->player_id);
	if (car->next)
		return (find_car(i, car->next));
	return (-1);
}

void	print_mem(t_war *war, int i, int player_id)
{
	static unsigned char	c[MEM_SIZE] = "";
	static int				count[MEM_SIZE];

	while (++i <= MEM_SIZE)
	{
		if (i && (i % 64) == 0)
		{
			attron(COLOR_PAIR(2));
			printw("   \n  ");
			attroff(COLOR_PAIR(2));
		}
		if (((player_id = find_car(i, war->cars)) != -1 ||
			c[i] != war->memory[i] || count[i]) && i != MEM_SIZE)
		{
			if (c[i] != war->memory[i])
				count[i] = 30;
			c[i] = war->memory[i];
			attron(COLOR_PAIR(player_id + 2));
			printw("%02hhx ", war->memory[i]);
			attroff(COLOR_PAIR(player_id + 2));
			count[i] -= ((player_id == -1) ? 1 : 0);
		}
		else if (i != MEM_SIZE)
			printw("%02hhx ", war->memory[i]);
	}
}

int		is_end(int cars[4])
{
	int i;
	int k;

	i = -1;
	k = 0;
	while (++i < 4)
		if (cars[i] == -1)
			k++;
	return (k);
}

void	print_ncurses1(t_war *war, t_list *champions, int i, int isend)
{
	int		y;

	erase();
	getmaxyx(stdscr, i, y);
	i = -1;
	attron(COLOR_PAIR(2));
	while (++i < y + 2)
		printw(" ");
	i = -1;
	while (++i < y)
		mvprintw(65, i, " ");
	attroff(COLOR_PAIR(2));
	move(1, 2);
	print_mem(war, -1, -1);
	i = chat_num(war, champions, -1, 0);
	mvprintw(4, 198, "Cycles passed: %d ", war->cycles_passed);
	mvprintw(5, 198, "Cycles to die: %d ", war->cycles_to_die);
	refresh();
	if (isend)
		getch();
	usleep(8580);
}
