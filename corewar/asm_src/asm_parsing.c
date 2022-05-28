/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfriesen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:57:25 by jfriesen          #+#    #+#             */
/*   Updated: 2019/03/19 18:57:28 by jfriesen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int			check_duplicate_label(char *s, t_info *info)
{
	t_operation *op;

	op = info->operations;
	while (op)
	{
		if (op->tokens->type == -1)
			if (!ft_strcmp(op->tokens->content, s))
				return (0);
		op = op->next;
	}
	return (1);
}

int			add_label_to_operation(char *line, t_info *info, int k)
{
	char		*s;
	t_token		*t;
	t_operation	*op;

	if (!(s = ft_strsub(line, 0, k)))
		error_exit("Something wrong with memory allocation.", 0, &line, &info);
	if (check_duplicate_label(s, info))
	{
		t = create_token(s);
		t->type = -1;
		op = create_operation(t);
		operation_push_back(op, &(info->operations));
		free(s);
		return (1);
	}
	free(s);
	return (0);
}

int			check_start(char **line, t_info **info)
{
	int		k;
	char	*new;

	k = 0;
	if (starts_with_command(*line))
	{
		if (!convert_string_to_operation(line, *info))
			error_exit("Something wrong with memalloc.", 0, line, info);
	}
	else if ((k = starts_with_label(*line)))
	{
		if (!add_label_to_operation(*line, *info, k))
			error_exit("Duplicate label", g_nline, line, info);
		if (!full_of_spaces(&((*line)[k + 1])))
		{
			new = ft_strdup(&((*line)[k + 1]));
			clean_string(line);
			check_start(&new, info);
		}
	}
	else
		error_exit("Lexical error", g_nline, line, info);
	clean_string(line);
	return (1);
}

void		parse_operations(char **line, t_info **info, int fd)
{
	int		ret;

	ret = 1;
	while (ret > 0)
	{
		if (!full_of_spaces(*line))
			check_start(line, info);
		clean_string(line);
		g_nline += (ret = get_next_line(fd, line));
	}
}

t_info		*lexical_analyzer(int fd)
{
	t_info		*info;
	char		*line;
	int			ret;

	g_nline = 0;
	info = info_create();
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		g_nline++;
		if (!full_of_spaces(line))
		{
			if (starts_with(line, COMMENT_CMD_STRING) ||
				starts_with(line, NAME_CMD_STRING))
				parse_name_and_comment(&line, &info, fd);
			else if (info->name == NULL || info->comment == NULL)
				error_exit("Name or comment was not found.", 0, &line, &info);
			else
				parse_operations(&line, &info, fd);
		}
		clean_string(&line);
	}
	return (info);
}
