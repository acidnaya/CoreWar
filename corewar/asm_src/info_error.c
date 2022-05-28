/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfriesen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:44:29 by jfriesen          #+#    #+#             */
/*   Updated: 2019/03/20 13:44:31 by jfriesen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void		free_operations(t_info *info)
{
	t_operation	*op;
	t_token		*t;
	t_operation	*next_op;
	t_token		*next_t;

	op = info->operations;
	while (op)
	{
		t = op->tokens;
		while (t)
		{
			next_t = t->next;
			free(t->content);
			free(t);
			t = next_t;
		}
		next_op = op->next;
		free(op);
		op = next_op;
	}
}

void		free_info(t_info *info)
{
	if (info)
	{
		if (info->name)
			free(info->name);
		if (info->comment)
			free(info->comment);
		if (info->operations)
			free_operations(info);
		free(info);
	}
}

void		print_error(char *string, int nline)
{
	if (nline)
		ft_printf("%s at line %d.\n", string, nline);
	else
		ft_printf("%s\n", string);
}

void		error_exit(char *string, int nline, char **line, t_info **info)
{
	print_error(string, nline);
	free_info(*info);
	clean_string(line);
	exit(0);
}

t_info		*info_create(void)
{
	t_info	*info;

	if (!(info = (t_info *)malloc(sizeof(t_info))))
		return (NULL);
	info->name = NULL;
	info->comment = NULL;
	info->operations = NULL;
	return (info);
}
