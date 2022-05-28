/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:45:24 by msnow-be          #+#    #+#             */
/*   Updated: 2018/11/19 16:49:08 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int pos;
	int ans;
	int sign;

	pos = 0;
	sign = 1;
	while (((str[pos] >= '\t') && (str[pos] <= '\r')) || (str[pos] == ' '))
		pos++;
	if (str[pos] == '-')
	{
		sign = -1;
		pos++;
	}
	else if (str[pos] == '+')
		pos++;
	ans = 0;
	while ((str[pos] >= '0') && (str[pos] <= '9'))
	{
		ans *= 10;
		ans += str[pos] - '0';
		pos++;
	}
	return (ans * sign);
}

