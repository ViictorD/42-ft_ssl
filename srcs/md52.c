/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md52.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 19:57:08 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/21 19:15:22 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			get_hex(char *buff, unsigned int c, int i)
{
	if (c > 16)
		get_hex(buff, c / 16, i + 1);
	else
		buff[i + 1] = '\0';
	if (c % 16 < 10)
		buff[i] = (c % 16) + 48;
	else
		buff[i] = (c % 16) + 87;
}

unsigned int	convert_little_endiant(unsigned int num)
{
	return (((num >> 24) & 0xff) | ((num << 8) & 0xff0000) |
			((num >> 8) & 0xff00) | ((num << 24) & 0xff000000));
}

unsigned int	leftrotate(unsigned int x, unsigned int c)
{
	return ((x << c) | (x >> (32 - c)));
}

unsigned int	rightrotate(unsigned int x, unsigned int c)
{
	return ((x >> c) | (x << (32 - c)));
}

void			reverse_string(char *str)
{
	char	buff[9];
	int		len;
	int		i;

	len = ft_strlen(str);
	i = -1;
	while (len + ++i < 8)
		buff[i] = '0';
	while (len > 0)
		buff[i++] = str[--len];
	buff[8] = '\0';
	i = -1;
	while (++i < 8)
		str[i] = buff[i];
	str[i] = '\0';
}
