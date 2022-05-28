/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraynor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 19:45:09 by mraynor           #+#    #+#             */
/*   Updated: 2019/02/19 19:45:12 by mraynor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		size_t_dir(char *content)
{
	if (!ft_strcmp(content, "zjmp") || !ft_strcmp(content, "ldi") ||
		!ft_strcmp(content, "sti") || !ft_strcmp(content, "fork") ||
		!ft_strcmp(content, "lldi") || !ft_strcmp(content, "lfork"))
		return (2);
	return (4);
}

void	find_size(t_operation *oper, int byte)
{
	t_token		*tok;

	while (oper)
	{
		tok = oper->tokens;
		if (tok->type != -1)
		{
			tok->bytes = 1;
			if (tok->next && (tok->next->next || tok->next->type != 2))
				tok->bytes = 2;
			byte = tok->bytes;
			while ((tok = tok->next))
			{
				if (tok->type == 4)
					tok->bytes = 1;
				else if (tok->type == 2)
					tok->bytes = size_t_dir(oper->tokens->content);
				else if (tok->type == 3)
					tok->bytes = 2;
				byte += tok->bytes;
			}
			oper->bytes = byte;
		}
		oper = oper->next;
	}
}

int		find_marker(t_info *info, char *cont, t_token *tok, int line)
{
	t_operation	*oper;
	int			to_mark;
	int			byte;
	int			to_tok;
	t_token		*t;

	to_tok = -1;
	to_mark = -1;
	byte = 0;
	oper = info->operations;
	while (oper)
	{
		t = oper->tokens;
		if (t->type == -1 && !ft_strcmp(&cont[1], t->content))
			to_mark = byte;
		while ((t = t->next))
			if (t == tok)
				to_tok = byte;
		byte += oper->bytes;
		oper = oper->next;
	}
	if (to_tok == -1 || to_mark == -1)
		err(info, 3, cont, line);
	return (to_mark - to_tok);
}

void	write_fail(t_info *info, int fd_new, t_operation *oper, int byte)
{
	char	c[4];

	write(fd_new, info->name, PROG_NAME_LENGTH + 8);
	oper = info->operations;
	while (oper)
	{
		byte += oper->bytes;
		oper = oper->next;
	}
	go_to_16(c, byte, 0, 4);
	write(fd_new, c, 4);
	write(fd_new, info->comment, COMMENT_LENGTH + 4);
	oper = info->operations;
	while (oper)
	{
		write(fd_new, oper->bin, oper->bytes);
		oper = oper->next;
	}
}

void	put_byte_code_into_newfile(char *newfilename, t_info *info)
{
	int			fd_new;
	t_operation	*oper;

	find_size(info->operations, 0);
	info->filname = newfilename;
	write_name(info, 0, info->name, info->comment);
	oper = info->operations;
	while (oper)
	{
		if (oper->tokens->type != -1)
			codinstr(oper, info, 4);
		oper = oper->next;
	}
	fd_new = open(newfilename, O_CREAT | O_TRUNC | O_RDWR, 0777);
	write_fail(info, fd_new, NULL, 0);
	close(fd_new);
	err(info, 4, NULL, 0);
}
