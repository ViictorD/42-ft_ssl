/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 15:17:33 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/23 17:33:02 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		get_hex(unsigned char *buff, unsigned long c, int i)
{
	if (c > 16)
		get_hex(buff, c / 16, i + 1);
	if (c % 16 < 10)
		buff[i] = (c % 16) + 48;
	else
		buff[i] = (c % 16) + 87;
}

void		strrev(unsigned char *str, unsigned long len)
{
	char			tmp;
	unsigned long	i;

	if (!str || !len)
		return ;
	i = 0;
	--len;
	while (i < len)
	{
		tmp = str[i];
		str[i] = str[len];
		str[len] = tmp;
		++i;
		--len;
	}
}
