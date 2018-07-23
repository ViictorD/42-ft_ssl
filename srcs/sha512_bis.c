/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:30:18 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/23 17:31:51 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*get_sha512_hash(unsigned long *h)
{
	unsigned char	buff_hex[8][16];
	char			*out;
	int				i;
	int				j;
	int				l;

	i = -1;
	while (++i < 8)
	{
		ft_memset(buff_hex[i], '0', 16);
		get_hex(buff_hex[i], h[i], 0);
		strrev(buff_hex[i], 16);
	}
	if (!(out = (char*)malloc(129)))
		ft_exiterror("Malloc failed.", 1);
	i = -1;
	j = -1;
	while (++i < 128)
	{
		if (!(i % 16) && (++j + 1))
			l = -1;
		out[i] = buff_hex[j][++l];
	}
	out[i] = '\0';
	return (out);
}

void	rev_64(unsigned char *str, unsigned long len)
{
	unsigned long	i;
	unsigned long	stop;
	unsigned char	*buffer;

	buffer = str;
	i = 0;
	stop = (len / 8 + 1) * 8;
	while (i < stop)
	{
		strrev(buffer + i, 8);
		i += 8;
	}
}
