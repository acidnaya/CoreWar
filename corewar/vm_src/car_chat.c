/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   car_chat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraynor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:14:34 by mraynor           #+#    #+#             */
/*   Updated: 2019/03/20 18:14:36 by mraynor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virt_m.h"

void	add_left(char **quotes, int *k, char *name, int i)
{
	char s;

	if (*k == 6 && (*k)--)
	{
		i = -1;
		free(quotes[0]);
		while (++i < 5)
			quotes[i] = quotes[i + 1];
	}
	quotes[*k] = ft_memalloc(300);
	quotes[*k][0] = 0;
	ft_strcpy(&quotes[*k][1], name);
	ft_strcat(&quotes[(*k)++][1], " left chat(");
}

void	chat(char **quotes, int *k, t_list *champions, int i)
{
	int		fd;
	char	s;

	while (i-- && champions)
		champions = champions->next;
	if (*k == 6 && (*k)--)
	{
		i = -1;
		free(quotes[0]);
		while (++i < 5)
			quotes[i] = quotes[i + 1];
	}
	quotes[*k] = (char *)ft_memalloc(300);
	quotes[*k][0] = ((t_champ *)champions->content)->player_num;
	ft_strcpy(&quotes[*k][1], ((t_champ *)champions->content)->bot_name);
	fd = open("img/epic", O_RDONLY);
	i = rand() % 35;
	while (i && read(fd, &s, 1) == 1)
		if (s == '\n')
			i--;
	i = ft_strlen(quotes[*k]);
	while (read(fd, &s, 1) == 1 && s != '\n')
		quotes[*k][i++] = s;
	quotes[(*k)++][i] = '\0';
	close(fd);
}

void	goodbay(char **quotes, int *k, char *name, int i)
{
	int		fd;
	char	s;
	int		j;

	if (*k == 6 && (*k)--)
	{
		j = -1;
		free(quotes[0]);
		while (++j < 5)
			quotes[j] = quotes[j + 1];
	}
	quotes[*k] = ft_memalloc(300);
	quotes[*k][0] = i;
	ft_strcpy(&quotes[*k][1], name);
	fd = open("img/goodbay", O_RDONLY);
	i = rand() % 5;
	while (i && read(fd, &s, 1) == 1)
		if (s == '\n')
			i--;
	i = ft_strlen(quotes[*k]);
	while (read(fd, &s, 1) == 1 && s != '\n')
		quotes[*k][i++] = s;
	quotes[(*k)++][i] = '\0';
	close(fd);
}

void	print_car(int cars[4], t_war *war, t_list *champions, int *k)
{
	static int	oldcar[4] = {-1, -1, -1, -1};
	int			i;
	int			t;
	int			j;

	i = -1;
	t = 0;
	while (++i < 4)
		if (cars[i] == -1 && oldcar[i] != -1)
		{
			goodbay(war->quotes, k, find_name(i, champions), i + 1);
			add_left(war->quotes, k, find_name(i, champions), 0);
			oldcar[i] = cars[i];
		}
		else if (cars[i] != -1)
		{
			oldcar[i] = cars[i];
			attron(COLOR_PAIR(3 + i));
			mvprintw(7 + t++, 198, " ");
			attroff(COLOR_PAIR(3 + i));
			printw(" - %d", cars[i]);
		}
}

int		chat_num(t_war *war, t_list *champions, int i, int m)
{
	static int	n1 = 4;
	static int	k = 0;
	int			cars[4];

	while (++i < 4)
		cars[i] = -1;
	m = count_car(war->cars, cars, 0);
	if (--n1 == 0)
	{
		while (++i > 4 || cars[i - 1] == -1 || (k > 2 && war->quotes[k - 1][0]
			== i && war->quotes[k - 2][0] == i && is_end(cars) < 3))
			i = rand() % m;
		chat(war->quotes, &k, champions, i - 1);
		n1 = 200 + rand() % 150;
	}
	print_car(cars, war, champions, &k);
	i = -1;
	while (++i < k)
	{
		attron(COLOR_PAIR(war->quotes[i][0] + 7));
		mvprintw(67 + i, 1, "%s", &war->quotes[i][1]);
		attroff(COLOR_PAIR(war->quotes[i][0] + 7));
	}
	((i = is_end(cars)) != 4) ? printw("\n someone writes") : 0;
	return (is_end(cars));
}
