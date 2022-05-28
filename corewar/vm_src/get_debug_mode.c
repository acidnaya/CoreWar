/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_debug_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:49:49 by msnow-be          #+#    #+#             */
/*   Updated: 2019/03/22 16:10:15 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "virt_m.h"

static void		get_nbr_cycles(t_debug_mode **debug, char **argv, int *arg_i)
{
	int pos;

	*arg_i += 1;
	pos = 0;
	while (argv[*arg_i][pos])
	{
		if (argv[*arg_i][pos] < '0' || argv[*arg_i][pos] > '9')
		{
			free(*debug);
			*debug = NULL;
			return ;
		}
		pos++;
	}
	(*debug)->dump = ft_atoi(argv[*arg_i]);
	*arg_i += 1;
}

t_debug_mode	*initialize_debug_mode(void)
{
	t_debug_mode	*debug;

	debug = (t_debug_mode *)malloc(sizeof(t_debug_mode));
	debug->dump = -1;
	debug->show_cycles = 0;
	debug->show_deaths = 0;
	debug->show_lives = 0;
	debug->show_ops = 0;
	debug->visualize = 0;
	debug->show_aff = 0;
	return (debug);
}

static void		add_debug_visual_options(t_debug_mode **debug, char opt)
{
	if (opt == 'c')
		(*debug)->show_cycles = 1;
	else if (opt == 'd')
		(*debug)->show_deaths = 1;
	else if (opt == 'l')
		(*debug)->show_lives = 1;
	else if (opt == 'o')
		(*debug)->show_ops = 1;
	else if (opt == 'v')
	{
		(*debug)->show_cycles = 0;
		(*debug)->show_deaths = 0;
		(*debug)->show_lives = 0;
		(*debug)->show_ops = 0;
		(*debug)->visualize = 1;
	}
	else
	{
		free(*debug);
		*debug = NULL;
		return ;
	}
}

static void		parse_next_flag(t_debug_mode **debug, char **argv, int *arg_i)
{
	int				pos;

	if (!ft_strncmp(argv[*arg_i], "-dump\0", 6))
		get_nbr_cycles(debug, argv, arg_i);
	else if (!ft_strncmp(argv[*arg_i], "-show\0", 6))
	{
		*arg_i += 1;
		pos = 0;
		while (*debug && argv[*arg_i][pos])
		{
			add_debug_visual_options(debug, argv[*arg_i][pos]);
			pos++;
		}
		*arg_i += 1;
	}
	else if (!ft_strncmp(argv[*arg_i], "-a\0", 3))
	{
		(*debug)->show_aff = 1;
		*arg_i += 1;
	}
}

t_debug_mode	*get_debug_mode(char **argv, int *arg_i)
{
	t_debug_mode	*debug;

	debug = initialize_debug_mode();
	while (debug && (!ft_strncmp(argv[*arg_i], "-dump\0", 6)
		|| !ft_strncmp(argv[*arg_i], "-show\0", 6)
		|| !ft_strncmp(argv[*arg_i], "-a\0", 3)))
	{
		parse_next_flag(&debug, argv, arg_i);
	}
	return (debug);
}
