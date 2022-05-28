/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:45:24 by msnow-be          #+#    #+#             */
/*   Updated: 2018/11/19 16:49:08 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_word_count(char const *s, char c)
{
	int	pos;
	int	res;

	if ((s == NULL) || (s[0] == '\0'))
		return (0);
	res = (s[0] != c);
	pos = 1;
	while (s[pos])
	{
		if (s[pos - 1] == c && s[pos] != c)
			res++;
		pos++;
	}
	return (res);
}

static int	next_word_len(const char *s, char c)
{
	int len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**res;
	int		w_count;
	int		word_index;
	int		i;

	w_count = get_word_count(s, c);
	if ((s == NULL) || !(res = (char**)malloc(sizeof(char*) * (w_count + 1))))
		return (NULL);
	word_index = 0;
	i = 0;
	while (word_index < w_count)
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (!(res[word_index] = ft_strsub(s, i, next_word_len(s + i, c))))
			return (NULL);
		while (s[i] != '\0' && s[i] != c)
			i++;
		word_index++;
	}
	res[word_index] = NULL;
	return (res);
}
