/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_name_com_im.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraynor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:22:59 by mraynor           #+#    #+#             */
/*   Updated: 2019/03/20 18:23:03 by mraynor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virt_m.h"
#define MAXLINE 12
#define CENTR(y, y1, x) (y + 2 + (y1 - 4 - x) / 2)
#define SH(y1) (y1 - 4)
#define ISEND(j, y1) ((j % SH(y1) == 0) ? 1 : 0)

int		print_char(int k, int len, int y, char c)
{
	char	s[2];
	int		i;
	int		fd;
	int		d;
	int		max;

	fd = open("img/alfa", O_RDONLY);
	i = (c - 33) * 5;
	while (i && (read(fd, s, 1)) == 1)
		if (s[0] == '\n')
			i--;
	d = k;
	max = 0;
	i = 0;
	while ((read(fd, s, 1)) == 1 && (k - d) != 5)
		if (s[0] == '\n')
		{
			k++;
			max = (i > max) ? i : max;
			i = 0;
		}
		else
			mvprintw(k, y + i++, "%c", s[0]);
	close(fd);
	return (max);
}

void	print_name(t_champ *ch, int k, int y, int y1)
{
	int		i;
	int		now;

	if (k < 0 || y < 0 || y1 < 0)
		return ;
	now = y;
	i = -1;
	attron(COLOR_PAIR(7 + ch->player_num));
	while (ch->bot_name[++i])
	{
		if (now + 6 > y + y1 || ch->bot_name[i] == '\n')
		{
			k += 5;
			now = y;
		}
		if (ch->bot_name[i] == ' ' && now + 6 > y + y1)
			i++;
		else if (ch->bot_name[i] == ' ')
			now += 3;
		if (ch->bot_name[i] >= 33 && ch->bot_name[i] <= 126)
			now += (print_char(k, 0, now, ch->bot_name[i]) + 1);
	}
	attroff(COLOR_PAIR(7 + ch->player_num));
}

void	print_norm_name(t_champ *ch, int k, int y, int y1)
{
	int		i;
	int		j;

	i = -1;
	if (k < 0 || y < 0 || y1 < 0)
		return ;
	attron(COLOR_PAIR(7 + ch->player_num));
	while (ch->bot_name[++i])
		if (i % (y1) == 0 || (ch->bot_name[i] == '\n' && ch->bot_name[i + 1] &&
			++i))
		{
			if (ft_strlen(&ch->bot_name[i]) / (y1) == 0)
				mvprintw(k++, y + 2 + (y1 - ft_strlen(&ch->bot_name[i]))
					/ 2, "%c", ch->bot_name[i]);
			else
				mvprintw(k++, y + 2, "%c", ch->bot_name[i]);
		}
		else if (ch->bot_name[i] != '\n')
			printw("%c", ch->bot_name[i]);
	attroff(COLOR_PAIR(7 + ch->player_num));
}

void	print_comment(int k, int y, t_champ *ch, int y1)
{
	int		i;
	int		d;

	i = -1;
	d = k;
	if (k < 0 || y < 0 || y1 < 0)
		return ;
	mvprintw(k, ft_strlen(&ch->bot_comment[0]) / (SH(y1)) ? (y + 1) :
		CENTR(y, y1, ft_strlen(&ch->bot_comment[0])) - 1, "\"");
	while (ch->bot_comment[++i])
		if (!(i % SH(y1)) && !(ft_strlen(&ch->bot_comment[i]) / SH(y1)))
		{
			mvprintw(k + 1, CENTR(y, y1, ft_strlen(&ch->bot_comment[i])),
				"© GRET CHEMPION");
			mvprintw(k++, CENTR(y, y1, ft_strlen(&ch->bot_comment[i])),
				"%c", ch->bot_comment[i]);
		}
		else if (i % SH(y1) == 0 || (ch->bot_comment[i] == '\n' &&
			ch->bot_comment[i + 1] && ++i))
			mvprintw(k++, y + 2, "%c", ch->bot_comment[i]);
		else if (ch->bot_comment[i] != '\n')
			printw("%c", ch->bot_comment[i]);
	printw("\"");
}

void	print_short_comment(int k, int y, char *com, int y1)
{
	int		i;
	int		d;
	int		j;

	i = -1;
	j = 0;
	d = k;
	if (k < 0 || y < 0 || y1 < 0)
		return ;
	mvprintw(k, ft_strlen(&com[0]) / (SH(y1)) ? (y + 1) :
		CENTR(y, y1, ft_strlen(&com[0])) - 1, "\"");
	while (com[++i])
		if (com[i] == '\n' && k - d >= MAXLINE - 1 && !printw("...\"") &&
			!mvprintw(k, y + 10, "© GRET CHEMPION"))
			return ;
		else if (ISEND(j, y1) && !ft_strchr(&com[i], '\n') &&
			!(ft_strlen(&com[i]) / SH(y1)) && !mvprintw(k + 1,
			CENTR(y, y1, ft_strlen(&com[i])), "© GRET CHEMPION")
			&& !mvprintw(k++, CENTR(y, y1, ft_strlen(&com[i])), "%c", com[i]))
			j = 1;
		else if (((ISEND(j, y1) || (com[i] == '\n' && com[i + 1] && ++i))
			&& !mvprintw(k++, y + 2, "%c", com[i])) || (com[i] != '\n' && ++j
			&& printw("%c", com[i])))
			j = 1;
	printw("\"");
}
