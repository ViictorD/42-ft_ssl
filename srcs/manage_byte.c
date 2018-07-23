/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_byte.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:26:29 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/23 17:27:47 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int	convert_little_endiant(unsigned int num)
{
	return (((num >> 24) & 0xff) | ((num << 8) & 0xff0000) |
			((num >> 8) & 0xff00) | ((num << 24) & 0xff000000));
}

unsigned int	leftrotate(unsigned int x, unsigned int c)
{
	return ((x << c) | (x >> (32 - c)));
}

unsigned int	rrot(unsigned int x, unsigned int c)
{
	return ((x >> c) | (x << (32 - c)));
}

unsigned long	rrot_l(unsigned long x, unsigned long c)
{
	return ((x >> c) | (x << (64 - c)));
}

unsigned int	uswap_32(unsigned int x)
{
	return (((((x) & 0xff000000u) >> 24) | (((x) & 0x00ff0000u) >> 8) | \
			(((x) & 0x0000ff00u) << 8) | (((x) & 0x000000ffu) << 24)));
}
