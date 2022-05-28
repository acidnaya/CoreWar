/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_vm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 15:42:01 by msnow-be          #+#    #+#             */
/*   Updated: 2019/03/22 15:23:45 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "virt_m.h"

void	del_champ(void *content)
{
	t_champ *champ;

	champ = (t_champ *)content;
	free(champ->bot_code);
	champ->bot_code = NULL;
	free(champ);
	champ = NULL;
}

void	del_car(void *content, size_t size)
{
	t_car *car;

	car = (t_car *)content;
	free(car);
	car = NULL;
	size++;
}

void	clear_champions(t_list **champions)
{
	t_list	*ptr;

	if (champions && *champions)
	{
		ptr = *champions;
		while (ptr)
		{
			del_champ(ptr->content);
			ptr = ptr->next;
		}
	}
	ft_lstdel_nocpy(champions);
}

void	clean_all(t_war *war, t_list **champions, t_debug_mode **debug)
{
	int		quote_index;

	if (war)
	{
		if (war->cars)
			ft_lstdel(&war->cars, del_car);
		if (war->quotes)
		{
			quote_index = 0;
			while (quote_index < 6)
			{
				free(war->quotes[quote_index]);
				quote_index++;
			}
			free(war->quotes);
			war->quotes = NULL;
		}
	}
	clear_champions(champions);
	if (debug && *debug)
	{
		free(*debug);
		*debug = NULL;
	}
}
