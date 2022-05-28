/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_viz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraynor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:31:08 by mraynor           #+#    #+#             */
/*   Updated: 2019/03/20 18:31:11 by mraynor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "virt_m.h"

void	print_imeg(int count, int y, int k)
{
	int		r;
	int		fd;
	char	s[7];
	int		i;

	if (k < 0 || y < 0)
		return ;
	ft_strcpy(s, "img/");
	s[4] = ((count <= 2) ? (rand() % 6) : (rand() % 5 + 4)) + 48;
	s[5] = '\0';
	fd = open(s, O_RDONLY);
	read(fd, s, 3);
	k -= ft_atoi(s) / 2;
	mvprintw(k++, y + 20, " ");
	i = 0;
	while (read(fd, s, 1) == 1)
		if (s[0] == '\n')
		{
			k++;
			i = 0;
		}
		else
			mvprintw(k, y + i++, "%c", s[0]);
	close(fd);
}

int		len_list(t_list *champions)
{
	if (!champions)
		return (0);
	return (len_list(champions->next) + 1);
}

char	*find_name(int i, t_list *champions)
{
	if (((t_champ *)champions->content)->player_num == i + 1)
		return (((t_champ *)champions->content)->bot_name);
	if (champions->next)
		return (find_name(i, champions->next));
	return (NULL);
}

int		count_car(t_list *car, int cars[4], int max)
{
	t_car *t;

	if (!car)
		return (max);
	t = (t_car *)car->content;
	if (cars[t->player_id - 1] == -1)
		cars[t->player_id - 1] = 1;
	else
		cars[t->player_id - 1]++;
	if (t->player_id > max)
		max = t->player_id;
	if (car->next)
		return (count_car(car->next, cars, max));
	return (max);
}
