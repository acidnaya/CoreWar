/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfriesen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:02:09 by jfriesen          #+#    #+#             */
/*   Updated: 2019/03/19 19:02:12 by jfriesen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int			is_label(char *s)
{
	int i;

	if (s)
	{
		i = 0;
		while (s[i] && ft_strchr(LABEL_CHARS, s[i]))
			i++;
		if (s[i] == LABEL_CHAR && !s[i + 1])
			return (1);
	}
	return (0);
}

t_token		*create_token(char *s)
{
	t_token	*t;

	if (!(t = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	t->content = strdup(s);
	t->type = 0;
	t->bytes = 0;
	t->next = NULL;
	return (t);
}

t_token		*token_push_back(t_token *new, t_token **first)
{
	t_token *ptr;

	ptr = *first;
	if (!*first)
	{
		*first = new;
		return (*first);
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	return (*first);
}

void		operation_push_back(t_operation *new, t_operation **first)
{
	t_operation *ptr;

	ptr = *first;
	if (!*first)
	{
		*first = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

t_operation	*create_operation(t_token *tokens)
{
	t_operation	*op;

	if (!(op = (t_operation *)malloc(sizeof(t_operation))))
		return (NULL);
	op->tokens = tokens;
	op->next = NULL;
	op->bytes = 0;
	op->strnum = -1;
	return (op);
}
