/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rew.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraynor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 03:18:23 by mraynor           #+#    #+#             */
/*   Updated: 2019/03/17 03:18:26 by mraynor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virt_m.h"

#define LEN 3
#define HEADER 9
#define COM43(x) (x + HEADER) / 2 - 12
#define COMY432(y) (y / 2 + LEN + 1)
#define NAM43(y) (y / 2 + LEN + 10)
#define LENCOM3(x, y) (y / 2 + x / 4 + 10)
#define STRCOM3(x, y) (y / 2 - x / 4 - 10)

void	print_2_player(t_list *champions, int x, int y, int i)
{
	t_champ		*ch;

	ch = (t_champ *)champions->content;
	print_name(ch, HEADER + 1, 1, y / 2 - LEN - 2);
	print_imeg(2, 20, (x + HEADER) / 2 - 3);
	print_comment((x + HEADER) / 2 + 13, 1, ch, y / 2 - LEN - 2);
	init_color(COLOR_CYAN, 599, 0, 0);
	attron(COLOR_PAIR(12));
	while (++i <= x - HEADER)
		mvprintw(x - i, y / 2 - LEN, "      ");
	attroff(COLOR_PAIR(12));
	ch = (t_champ *)champions->next->content;
	print_name(ch, HEADER + 1, COMY432(y), y / 2 - LEN - 2);
	print_imeg(2, y / 2 + LEN + 21, (x + HEADER) / 2 - 3);
	print_comment((x + HEADER) / 2 + 13, COMY432(y), ch, y / 2 - LEN - 2);
}

void	print_4_player(t_list *champions, int x, int y, int i)
{
	t_champ		*ch;

	ch = (t_champ *)champions->content;
	print_norm_name(ch, HEADER + 1, 10, y / 2 - LEN - 20);
	print_imeg(3, 21, (x / 2 - 5 + HEADER) / 2);
	print_short_comment(COM43(x), 1, ch->bot_comment, y / 2 - LEN - 2);
	ch = (t_champ *)(champions->next->content);
	print_norm_name(ch, HEADER + 1, NAM43(y), y / 2 - LEN - 20);
	print_imeg(3, y / 2 + LEN + 21, (x / 2 - 5 + HEADER) / 2);
	print_short_comment(COM43(x), COMY432(y), ch->bot_comment, y / 2 - LEN - 2);
	ch = (t_champ *)champions->next->next->content;
	print_norm_name(ch, (x + HEADER) / 2 + 2, NAM43(y), y / 2 - LEN - 20);
	print_imeg(3, y / 2 + LEN + 21, x - 22);
	print_short_comment(x - 12, COMY432(y), ch->bot_comment, y / 2 - LEN - 2);
	ch = (t_champ *)champions->next->next->next->content;
	print_norm_name(ch, (x + HEADER) / 2 + 2, 10, y / 2 - LEN - 20);
	print_imeg(3, 21, x - 22);
	print_short_comment(x - 12, 1, ch->bot_comment, y / 2 - LEN - 2);
	attron(COLOR_PAIR(12));
	while (++i <= x - HEADER)
		mvprintw(x - i, y / 2 - LEN, "      ");
	i = -1;
	while (++i <= y)
		mvprintw((x + HEADER) / 2, i, " ");
	attroff(COLOR_PAIR(12));
}

void	print_3_player(t_list *champions, int x, int y, int i)
{
	t_champ		*ch;

	ch = (t_champ *)champions->content;
	print_norm_name(ch, HEADER + 1, 10, y / 2 - LEN - 20);
	print_imeg(3, 21, (x / 2 - 5 + HEADER) / 2);
	print_short_comment(COM43(x), 1, ch->bot_comment, y / 2 - LEN - 2);
	ch = (t_champ *)champions->next->content;
	print_norm_name(ch, HEADER + 1, NAM43(y), y / 2 - LEN - 20);
	print_imeg(3, y / 2 + LEN + 21, (x / 2 - 5 + HEADER) / 2);
	print_short_comment(COM43(x), COMY432(y), ch->bot_comment, y / 2 - LEN - 2);
	ch = (t_champ *)champions->next->next->content;
	print_norm_name(ch, (x + HEADER) / 2 + 5, 10, y - 20);
	print_imeg(1, 25, x - 19);
	print_comment((x + HEADER) / 2 + 10, STRCOM3(x, y), ch, LENCOM3(x, y));
	attron(COLOR_PAIR(12));
	while (++i <= (x) / 2 + 1)
		mvprintw(i, y / 2 - LEN, "      ");
	i = -1;
	while (++i <= y)
		mvprintw((x + HEADER) / 2, i, " ");
	attroff(COLOR_PAIR(12));
}

void	print_head(int x, int y, int i, int k)
{
	char	s[2];
	int		v;
	int		fd;

	fd = open("img/corw", O_RDONLY);
	v = (y / 2 - 33) <= 0 ? 1 : (y / 2 - 33);
	mvprintw(1, v - 1, " ");
	attron(COLOR_PAIR(14));
	while ((read(fd, s, 1)) == 1)
		if (s[0] == '\n' && read(fd, s, 1) == 1)
			mvprintw(k++, v, "%c", s[0]);
		else
			printw("%c", s[0]);
	attroff(COLOR_PAIR(14));
	close(fd);
	attron(COLOR_PAIR(12));
	i = -1;
	while (++i < y)
		mvprintw(0, i, " ");
	i = -1;
	while (++i < y)
		mvprintw(k, i, " ");
	attroff(COLOR_PAIR(12));
}

void	print_champ(t_list *champions, int i, int x, int y)
{
	char	s[2];
	int		fd;

	getmaxyx(stdscr, x, y);
	print_head(x, y, -1, 2);
	if (len_list(champions) == 3)
		print_3_player(champions, x, y, HEADER - 1);
	else if (len_list(champions) == 4)
		print_4_player(champions, x, y, -1);
	else if (len_list(champions) == 2)
		print_2_player(champions, x, y, -1);
	else
		return ;
	fd = open("img/vs", O_RDONLY);
	i = 2;
	mvprintw((x + HEADER) / 2 - i - 1, y / 2 - 11, " ");
	attron(COLOR_PAIR(14));
	while ((read(fd, s, 1)) == 1)
		if (s[0] == '\n' && read(fd, s, 1) == 1)
			mvprintw((x + HEADER) / 2 - i--, y / 2 - 10, "%c", s[0]);
		else
			printw("%c", s[0]);
	attroff(COLOR_PAIR(14));
	close(fd);
	refresh();
}
