/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_date.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 13:22:46 by msnow-be          #+#    #+#             */
/*   Updated: 2018/12/19 18:01:01 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_month(int num)
{
	char	**months;

	months = (char *[]){"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug",
		"Sep", "Oct", "Nov", "Dec"};
	if (num >= 1 && num <= 12)
		return (months[num - 1]);
	else
		return (0);
}

t_date	get_date(char *date)
{
	t_date	res;
	int		month;

	res.is_valid = 1;
	if (ft_strlen(date) == 10 && (date[4] == '-' || date[4] == '/')
		&& date[4] == date[7])
	{
		res.year = ft_atoi(date);
		month = ft_atoi(date + 5);
		res.month = get_month(month);
		res.day = ft_atoi(date + 8);
	}
	else if (ft_strlen(date) == 8)
	{
		res.year = ft_atoi(date) / 10000;
		month = ft_atoi(date + 4) / 100;
		res.month = get_month(month);
		res.day = ft_atoi(date + 6);
	}
	else
		res.is_valid = 0;
	if (res.year < 0 || res.year > 9999 || month < 1 || month > 12
		|| res.day < 0 || res.day > 31)
		res.is_valid = 0;
	return (res);
}

int		print_date(char *date_str, t_format format)
{
	int		date_length;
	t_date	date;

	if (!date_str)
		return (ft_printf("%s", "invalid date format"));
	date = get_date(date_str);
	if (date.is_valid == 0)
		return (ft_printf("%s", "invalid date format"));
	date_length = 10;
	if (!(format.left_align) && (format.width > date_length))
		put_fill(format.filler, format.width - date_length);
	ft_printf("%d-%s-%d", date.year, date.month, date.day);
	if (format.left_align && (format.width > date_length))
		put_fill(' ', format.width - date_length);
	return (format.width > date_length ? format.width : date_length);
}
