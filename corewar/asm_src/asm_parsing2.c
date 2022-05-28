/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfriesen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:48:11 by jfriesen          #+#    #+#             */
/*   Updated: 2019/03/20 13:48:13 by jfriesen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int			get_res(char *line, char **res)
{
	char	*new;
	int		ind;

	ind = ft_strchr_index(line, '"');
	if (!*res && ind >= 0)
		*res = ft_strsub(line, ind + 1, ft_strlen(line) - ind - 1);
	else if (*res)
	{
		new = ft_strjoin(*res, "\n");
		clean_string(res);
		*res = ft_strjoin(new, line);
	}
	ind = 0;
	if (!*res)
		return (0);
	while ((*res)[ind])
	{
		if ((*res)[ind] == '"' && full_of_spaces(&((*res)[ind + 1])))
			(*res)[ind] = '\0';
		else
			ind++;
	}
	return (1);
}

char		*get_name_or_comment(int fd, char **line)
{
	int			quote;
	char		*res;
	int			ret;

	res = NULL;
	quote = 0;
	ret = 1;
	delete_first_word(line);
	delete_spaces_from_start(line);
	if (**line != '"')
		return (NULL);
	while (quote < 2 && ret > 0)
	{
		quote += ft_count_chr(*line, '"');
		if (!(get_res(*line, &res)))
			return (NULL);
		clean_string(line);
		if (quote < 2)
			g_nline += (ret = get_next_line(fd, line));
	}
	if (quote < 2 && res)
		clean_string(&res);
	return (res);
}

void		parse_name_and_comment(char **line, t_info **info, int fd)
{
	if (starts_with(*line, COMMENT_CMD_STRING) && !((*info)->comment))
	{
		if (!((*info)->comment = get_name_or_comment(fd, line)))
			error_exit("Comment was not found", g_nline, line, info);
		if (ft_count_chr((*info)->comment, '"'))
			error_exit("Error", g_nline, line, info);
	}
	else if (starts_with(*line, NAME_CMD_STRING) && !((*info)->name))
	{
		if (!((*info)->name = get_name_or_comment(fd, line)))
			error_exit("Name was not found", g_nline, line, info);
		if (ft_count_chr((*info)->name, '"'))
			error_exit("Error", g_nline, line, info);
	}
	else if (starts_with(*line, NAME_CMD_STRING) && (*info)->name)
		error_exit("Duplicate name", g_nline, line, info);
	else if (starts_with(*line, COMMENT_CMD_STRING) && (*info)->comment)
		error_exit("Duplicate comment", g_nline, line, info);
}

t_operation	*char_array_to_operation(char **a)
{
	int			i;
	t_token		*t;
	t_token		*first_t;
	t_operation *op;

	i = 0;
	t = NULL;
	op = NULL;
	first_t = NULL;
	while (a && a[i] && a[i][0] != COMMENT_CHAR)
	{
		t = create_token(a[i]);
		token_push_back(t, &first_t);
		i++;
	}
	if (t)
		op = create_operation(first_t);
	return (op);
}

int			convert_string_to_operation(char **line, t_info *info)
{
	char		s[3];
	char		*spaces;
	char		**a;
	t_operation	*op;

	s[0] = SEPARATOR_CHAR;
	s[1] = COMMENT_CHAR;
	s[1] = '\0';
	spaces = ft_strjoin(SPACES, s);
	put_space_before_direct_char(line);
	a = ft_strsplit_symbols(*line, spaces);
	free(spaces);
	if (a)
	{
		op = char_array_to_operation(a);
		op->strnum = g_nline;
		assign_type(op);
		operation_push_back(op, &(info->operations));
		clean_array(&a);
		if (!check_syntax(op))
			error_exit("Syntax error", g_nline, line, &info);
	}
	else
		return (0);
	return (1);
}
