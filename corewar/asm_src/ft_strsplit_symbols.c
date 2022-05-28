/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfriesen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 15:49:13 by jfriesen          #+#    #+#             */
/*   Updated: 2018/11/27 15:49:15 by jfriesen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "assembler.h"

static int		ft_s(char s, char *c)
{
	int		k;

	k = 0;
	if (s == '\0')
		return (0);
	while (c[k])
	{
		if (s == c[k])
			return (0);
		k++;
	}
	return (1);
}

static char		**ft_mem(char **words, char *str, char *c)
{
	int num;
	int i;
	int j;

	i = 1;
	j = 0;
	num = 1;
	if (ft_s(str[0], c) == 1)
		num = 2;
	while (str[i] != '\0')
	{
		if ((ft_s(str[i - 1], c) == 0) && (ft_s(str[i], c) == 1))
			num++;
		i++;
	}
	if (!(words = (char **)malloc(num * sizeof(char *))))
		return (NULL);
	words[num - 1] = 0;
	return (words);
}

static void		ft_copy(char *word, char *str, int i, int f)
{
	int a;

	a = 0;
	while (f < i)
	{
		word[a] = str[f];
		f++;
		a++;
	}
	word[a] = '\0';
}

static char		**ft_clean(char ***a, int k)
{
	while (k >= 0)
	{
		free((*a)[k]);
		(*a)[k] = NULL;
		k--;
	}
	free(*a);
	*a = NULL;
	return (NULL);
}

char			**ft_strsplit_symbols(char *str, char *c)
{
	char	**words;
	int		f;
	int		i;
	int		j;
	int		k;

	words = NULL;
	if ((str == NULL) || (!str[0]) || (!(words = ft_mem(words, str, c))))
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	f = 0;
	while (str[i] != '\0')
		i++;
	while (++j <= i)
		if ((ft_s(str[j - 1], c) == 0) && (ft_s(str[j], c) == 1))
			f = j;
		else if ((ft_s(str[j - 1], c) == 1) && (ft_s(str[j], c) == 0))
		{
			if (!(words[k] = (char *)malloc((j - f + 1) * sizeof(char))))
				return (ft_clean(&words, k - 1));
			ft_copy(words[k++], str, j, f);
		}
	return (words);
}
