/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraynor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:00:36 by mraynor           #+#    #+#             */
/*   Updated: 2019/03/15 14:00:39 by mraynor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		ft_atoi_my(char *str)
{
	unsigned int	rez;
	int				i;
	int				sig;

	rez = 0;
	i = 0;
	sig = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		sig -= (str[i] == '-') * 2;
		i++;
	}
	while (str[i] - '0' <= 9 && str[i] - '0' >= 0)
	{
		if (rez > 2147483648 - (sig + 1) / 2)
			return (sig == -1 ? 0 : -1);
		rez = rez * 10 + str[i] - '0';
		i++;
	}
	if (str[i])
		return (-1);
	return ((int)rez * sig);
}

int		go_to_16(char *str, int c1, int i, int size)
{
	unsigned int	c;
	int				len;
	unsigned int	k;

	c = (size == 2) ? (unsigned short int)c1 : c1;
	if (size == 4)
		c = (unsigned int)c1;
	k = c;
	len = 1;
	while (k)
		if ((k /= 16 * 16) != 0)
			len++;
	size = (size == 0) ? len : size;
	if (size < len)
		return (-1);
	k = size;
	while (size--)
	{
		if (c)
			str[i + size] = c % (16 * 16);
		else
			str[i + size] = 0;
		c /= 16 * 16;
	}
	return (k + i);
}

void	read_arg(int *j, t_operation *oper, t_info *info, t_token *tok)
{
	int		k;

	if (tok->type == 2)
	{
		if (tok->content[1] != ':')
		{
			k = ft_atoi_my(&tok->content[1]);
			*j = go_to_16(oper->bin, k, *j, tok->bytes);
		}
		else
			*j = go_to_16(oper->bin, find_marker(info,
				&tok->content[1], tok, oper->strnum), *j, tok->bytes);
	}
	if (tok->type == 3)
	{
		if (tok->content[0] != ':')
		{
			k = ft_atoi_my(&tok->content[0]);
			*j = go_to_16(oper->bin, k, *j, tok->bytes);
		}
		else
			*j = go_to_16(oper->bin, find_marker(info,
				&tok->content[0], tok, oper->strnum), *j, tok->bytes);
	}
}

int		codinstr(t_operation *oper, t_info *info, int num)
{
	t_token		*tok;
	int			j;
	int			arg;

	tok = oper->tokens;
	j = tok->bytes;
	go_to_16(oper->bin, tok->type, 0, 1);
	arg = 0;
	while ((tok = tok->next) && --num)
		if (tok->type == 4)
		{
			arg = arg | (1 << (num * 2));
			j = go_to_16(oper->bin, ft_atoi_my(&tok->content[1]), j, 1);
		}
		else if (tok->type == 2 || tok->type == 3)
		{
			arg = arg | (1 << (num * 2 + 1));
			arg = (tok->type == 3) ? arg | (1 << (num * 2)) : arg;
			read_arg(&j, oper, info, tok);
		}
	if (oper->tokens->next->next || oper->tokens->next->type != 2)
		go_to_16(oper->bin, arg, 1, 1);
	return (1);
}

void	write_name(t_info *info, int i, char *del, char *del2)
{
	char	*val;

	val = info->name;
	info->name = (char *)ft_memalloc(PROG_NAME_LENGTH + 8 + 1);
	i = go_to_16(info->name, COREWAR_EXEC_MAGIC, 0, 4);
	while (*val && PROG_NAME_LENGTH + 4 > i)
		i = go_to_16(info->name, *val++, i, 0);
	if (*val && write(1, "Champion name too long (Max length 128)\n", 40))
		err(info, 1, del, 0);
	free(del);
	i = 0;
	val = info->comment;
	info->comment = (char *)ft_memalloc(COMMENT_LENGTH + 4 + 1);
	while (*val && COMMENT_LENGTH > i)
		i = go_to_16(info->comment, *val++, i, 0);
	if (*val && write(1, "Champion comment too long (Max length 2048)\n", 44))
		err(info, 1, del2, 0);
	free(del2);
}
