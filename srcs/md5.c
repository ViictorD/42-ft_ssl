/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 20:02:35 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/23 15:40:21 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char g_r[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

static unsigned int g_k[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

static unsigned int	fill_message(unsigned char **content, unsigned long len)
{
	unsigned int	mod;
	unsigned char	*buff;

	mod = 64 + (64 * (len / 64)) - len;
	if (mod < 9)
		mod += 64;
	if (!(buff = (unsigned char*)malloc(len + mod)))
		ft_exiterror("Malloc failed", 1);
	ft_memcpy(buff, *content, len);
	buff[len] = 0x80;
	ft_bzero(buff + len + 1, mod - 1);
	buff[len + mod - 1] = (char)(len * 8 >> (8 * 7));
	buff[len + mod - 2] = (char)(len * 8 >> (8 * 6));
	buff[len + mod - 3] = (char)(len * 8 >> (8 * 5));
	buff[len + mod - 4] = (char)(len * 8 >> (8 * 4));
	buff[len + mod - 5] = (char)(len * 8 >> (8 * 3));
	buff[len + mod - 6] = (char)(len * 8 >> (8 * 2));
	buff[len + mod - 7] = (char)(len * 8 >> (8 * 1));
	buff[len + mod - 8] = (char)(len * 8 >> (8 * 0));
	*content = buff;
	return (mod + len);
}

static void			main_loop2(t_data *data, unsigned int *f, unsigned int *g, \
					int i)
{
	if (i < 16)
	{
		*f = (data->b & data->c) | ((~data->b) & data->d);
		*g = i;
	}
	else if (i < 32)
	{
		*f = (data->d & data->b) | ((~data->d) & data->c);
		*g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		*f = data->b ^ data->c ^ data->d;
		*g = (3 * i + 5) % 16;
	}
	else
	{
		*f = data->c ^ (data->b | (~(data->d)));
		*g = (7 * i) % 16;
	}
}

static void			main_loop(t_data *data, unsigned char *content, \
					unsigned int offset)
{
	unsigned int	*m;
	unsigned int	f;
	unsigned int	g;
	int				i;

	data->a = data->out[0];
	data->b = data->out[1];
	data->c = data->out[2];
	data->d = data->out[3];
	m = (unsigned int*)((void*)content + offset);
	i = -1;
	while (++i < 64)
	{
		main_loop2(data, &f, &g, i);
		f = f + data->a + g_k[i] + m[g];
		data->a = data->d;
		data->d = data->c;
		data->c = data->b;
		data->b = data->b + leftrotate(f, g_r[i]);
	}
}

static char			*get_md5_hash(unsigned int *h)
{
	char			*out;
	unsigned char	buff_hex[4][8];
	int				i;
	int				j;
	int				l;

	i = -1;
	while (++i < 4)
	{
		ft_memset(buff_hex[i], '0', 8);
		get_hex(buff_hex[i], convert_little_endiant(h[i]), 0);
		strrev(buff_hex[i], 8);
	}
	if (!(out = (char*)malloc(33)))
		ft_exiterror("Malloc failed.", 1);
	i = -1;
	j = -1;
	while (++i < 32)
	{
		if ((!i || i == 8 || i == 16 || i == 24) && (++j + 1))
			l = -1;
		out[i] = buff_hex[j][++l];
	}
	out[i] = '\0';
	return (out);
}

char				*md5(unsigned char *content, unsigned long size)
{
	unsigned int	msg_len;
	unsigned int	offset;
	char			*out;
	t_data			*data;

	if (!(data = malloc(sizeof(struct s_data))))
		ft_exiterror("Malloc failed.", 1);
	data->out[0] = 0x67452301;
	data->out[1] = 0xefcdab89;
	data->out[2] = 0x98badcfe;
	data->out[3] = 0x10325476;
	msg_len = fill_message(&content, size);
	offset = 0;
	while (offset < msg_len && (offset += 64))
	{
		main_loop(data, content, offset - 64);
		data->out[0] += data->a;
		data->out[1] += data->b;
		data->out[2] += data->c;
		data->out[3] += data->d;
	}
	out = get_md5_hash(data->out);
	free(data);
	free(content);
	return (out);
}
