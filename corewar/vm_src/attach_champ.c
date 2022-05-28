/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attach_champ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 13:10:26 by msnow-be          #+#    #+#             */
/*   Updated: 2019/03/14 16:21:20 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virt_m.h"
#include "libft.h"
#include "op.h"

/*
** Checks whether yhere is already a player with this number
*/

_Bool	player_num_ok(int num, t_list *champs_list)
{
	t_champ *ch;

	while (champs_list)
	{
		ch = (t_champ *)champs_list->content;
		if (ch->player_num == num)
			return (0);
		champs_list = champs_list->next;
	}
	return (1);
}

/*
** Gets the next available number
*/

int		get_next_num(t_list *champs_list)
{
	int current;

	current = 1;
	while (!player_num_ok(current, champs_list))
		current++;
	return (current);
}

/*
** Checks whether the player who has this number had it auto-assigned
** (not parsed from the standart input)
*/

_Bool	num_was_auto_assigned(int num, t_list *champs_list)
{
	t_champ *ch;

	while (champs_list)
	{
		ch = (t_champ *)champs_list->content;
		if (ch->player_num == num)
			return (ch->num_auto_assigned);
		champs_list = champs_list->next;
	}
	return (0);
}

/*
** Replace previously auto-assigned number with a new number
** Signalizes failure if the number was parsed from the standart input
*/

_Bool	replace_auto_assigned(t_list *champs_list, int num)
{
	t_champ	*ch;
	int		next_num;

	if (!num_was_auto_assigned(num, champs_list))
		return (0);
	next_num = get_next_num(champs_list);
	while (champs_list)
	{
		ch = (t_champ *)champs_list;
		if (ch->player_num == num)
			ch->player_num = next_num;
		champs_list = champs_list->next;
	}
	return (1);
}

_Bool	attach_champ(t_champ *champ, t_list **champs_list, _Bool *error_shown)
{
	t_list	*lst;

	if (!(lst = ft_lstnew_nocpy(champ, sizeof(t_champ *))))
		return (0);
	if (!(*champs_list))
	{
		*champs_list = lst;
		if (champ->player_num == -1)
			champ->player_num = 1;
	}
	else
	{
		if (champ->player_num == -1)
			champ->player_num = get_next_num(*champs_list);
		else if (!player_num_ok(champ->player_num, *champs_list) &&
			!replace_auto_assigned(*champs_list, champ->player_num))
		{
			ft_putendl("Error: Duplicate player numbers!");
			*error_shown = 1;
			free(lst);
			return (0);
		}
		ft_lst_push_back(*champs_list, lst);
	}
	return (1);
}
