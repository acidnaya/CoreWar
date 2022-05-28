/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 13:27:42 by msnow-be          #+#    #+#             */
/*   Updated: 2019/02/22 16:19:41 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	first_bits(unsigned char ch)
{
	return (ch >> 6);
}

unsigned char	second_bits(unsigned char ch)
{
	ch = ch >> 4;
	return (ch & 0b11);
}

unsigned char	third_bits(unsigned char ch)
{
	ch = ch >> 2;
	return (ch & 0b11);
}
