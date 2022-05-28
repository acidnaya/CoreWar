/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_assignment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfriesen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:13:56 by jfriesen          #+#    #+#             */
/*   Updated: 2019/03/19 19:13:58 by jfriesen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int			check_syntax(t_operation *op)
{
	int		i;
	t_token *t;

	i = 0;
	t = op->tokens;
	while (t)
	{
		i = i * 10 + t->type;
		t = t->next;
	}
	if (i == 12 || i == 224 || i == 234 || i == 344 || i == 343 || i == 4444 ||
	i == 5444 || i == 6444 || i == 6424 || i == 6434 || i == 6244 || i == 6224
	|| i == 6234 || i == 6344 || i == 6334 || i == 6324 || i == 7444 ||
	i == 7424 || i == 7434 || i == 7244 || i == 7224 || i == 7234 || i == 7344
	|| i == 7334 || i == 7324 || i == 8444 || i == 8424 || i == 8434 ||
	i == 8244 || i == 8224 || i == 8234 || i == 8344 || i == 8334 || i == 8324
	|| i == 92 || i == 10444 || i == 10424 || i == 10244 || i == 10224 ||
	i == 10344 || i == 10324 || i == 11444 || i == 11442 || i == 11424 ||
	i == 11422 || i == 11434 || i == 11432 || i == 122 || i == 1324 || i == 1334
	|| i == 14444 || i == 14424 || i == 14244 || i == 14224 || i == 14344
	|| i == 14324 || i == 152 || i == 164)
		return (1);
	return (0);
}

void		assign_type(t_operation *op)
{
	t_token *t;

	t = op->tokens;
	while (t)
	{
		if (starts_with_command(t->content))
			t->type = command_type(t->content);
		else if ((t->content)[0] == DIRECT_CHAR
		&& (t->content)[1] == LABEL_CHAR)
			t->type = 2;
		else if ((t->content)[0] == DIRECT_CHAR && is_num(&((t->content)[1])))
			t->type = 2;
		else if ((t->content)[0] == LABEL_CHAR || is_num(t->content))
			t->type = 3;
		else if ((t->content)[0] == 'r' &&
		ft_atoi(&((t->content)[1])) <= REG_NUMBER &&
		ft_atoi(&((t->content)[1])) > 0)
			t->type = 4;
		t = t->next;
	}
}

void		err(t_info *info, int i, char *c, int line)
{
	if (i == 1 || i == 2)
		free(c);
	if (i == 3)
	{
		write(1, "No such label \"", 15);
		write(1, c, ft_strlen(c));
		write(1, "\" at line ", 10);
		ft_putnbr(line);
	}
	if (i == 4)
	{
		write(1, "Writing output program to ", 26);
		write(1, info->filname, ft_strlen(info->filname));
	}
	if (i == 3 || i == 4)
		write(1, "\n", 1);
	free(info->filname);
	free_info(info);
	exit(0);
}
