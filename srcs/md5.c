	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 20:56:54 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/12 22:11:29 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "../libft/libft.h"

void	fill_message(void **content)
{
	long	len;
	int		mod;
	int		nb_add;
	void 	*buff;
	int		i;

	len = ft_strlen((char*)*content);
	mod = 64 + (64 * (len / 64)) - len; // nb de bytes a file
	if (mod < 9)
		mod += 64;
	if (!(buff = malloc(len + mod)))
		ft_exiterror("Malloc failed", 1);
	ft_strcpy(buff, (char*)*content);
	((char*)buff)[len] = 0x80; // ajoute le 1
	i = -1;
	while (mod > 8)
		((char*)buff)[len + ++i] = 0;
	// len in little endiant
	((char*)buff)[len + ++i] = len & 0xFF;
	((char*)buff)[len + ++i] = len & 0xFF00;
	((char*)buff)[len + ++i] = len & 0xFF0000;
	((char*)buff)[len + ++i] = len & 0xFF000000;
	((char*)buff)[len + ++i] = len & 0xFF00000000;
	((char*)buff)[len + ++i] = len & 0xFF0000000000;
	((char*)buff)[len + ++i] = len & 0xFF000000000000;
	((char*)buff)[len + ++i] = len & 0xFF00000000000000;
}

static void		init_value(unsigned char *arr, char v1, char v2, char v3, char v4)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		arr[(i * 4)] = v1;
		arr[1 + (i * 4)] = v2;
		arr[2 + (i * 4)] = v3;
		arr[3 + (i * 4)] = v4;
	}
}

void	init_const(char *arr)
{
	unsigned char c[64];
	int				i;

	init_value(c, 7, 12, 17, 22);
	init_value(c + 16, 5, 9, 14, 20);
	init_value(c + 32, 4, 11, 16, 23);
	init_value(c + 48, 6, 10, 15, 21);

	i = -1;
	while (++i < 64)
		arr[i] = floor(ABS(sin(i + 1)) * pow(2, 32));
}

char	*md5(void *content)
{
	short	arr[16];
	char	const_arr[64];
	int 	i;
	char	*tmp;

	int		f;
	int		g;
	int		tmp2;

	// remplissage
	fill_message(&content);
	return (content);
	tmp = content;
	init_const(const_arr);
	i = -1;
	while (tmp)
	{
		int a = H0;
		int b = H1;
		int c = H2;
		int d = H3;
		// fill_512(arr, tmp);
		while (++i < 63)
		{
			if (i >= 0 && i <= 15)
			{
				f = (b & c) || ((!b) & d);
				g = i;
			}
			else if (i >= 16 && i <= 31)
			{
				f = (d & b) || ((!d) & c);
				g = (5 * i + 1) % 16;
			}
			else if (i >= 32 && i <= 47)
			{
				f = b ^ c ^ d;
				g = (3 * i) % 16;
			}
			else
			{
				f = c ^ (b ||(!d));
				g = (7 * i) % 16;
			}
		}
		tmp2 = d;
		d = c;
		c = b;
		// b = ((a + f + k[i] + w[g]) leftrotate r[i]) + b
		// a = temp
		tmp += 64;
	}

	return (content);
}