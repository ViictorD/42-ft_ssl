/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 18:11:33 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/21 22:50:36 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static unsigned int g_k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

static size_t	fill_message_sha256(unsigned char **msg, unsigned long len)
{
	unsigned int	mod;
	unsigned char	*buff;

	mod = 64 + (64 * (len / 64)) - len;
	if (mod < 9)
		mod += 64;
	if (!(buff = (unsigned char*)malloc(len + mod)))
		ft_exiterror("Malloc failed", 1);
	ft_memcpy(buff, *msg, len);
	buff[len] = 0x80;
	ft_bzero(buff + len + 1, mod - 1);
	buff[len + mod - 8] = (char)((len * 8) >> (8 * 7));
	buff[len + mod - 7] = (char)((len * 8) >> (8 * 6));
	buff[len + mod - 6] = (char)((len * 8) >> (8 * 5));
	buff[len + mod - 5] = (char)((len * 8) >> (8 * 4));
	buff[len + mod - 4] = (char)((len * 8) >> (8 * 3));
	buff[len + mod - 3] = (char)((len * 8) >> (8 * 2));
	buff[len + mod - 2] = (char)((len * 8) >> (8 * 1));
	buff[len + mod - 1] = (char)((len * 8) >> (8 * 0));
	*msg = buff;
	return (mod + len);
}

static void	main_loop_sha2562(t_sha256 *s, unsigned int *w, unsigned int *s0, unsigned int *s1)
{
	unsigned int	ch;
	unsigned int	tmp;
	unsigned int	tmp2;

	*s1 = rightrotate(s->e, 6) ^ rightrotate(s->e, 11) ^ rightrotate(s->e, 25);
	ch = (s->e & s->f) ^ ((~s->e) & s->g);
	tmp = s->h + *s1 + ch + g_k[s->i] + w[s->i];
	*s0 = rightrotate(s->a, 2) ^ rightrotate(s->a, 13) ^ rightrotate(s->a, 22);
	tmp2 = *s0 + ((s->a & s->b) ^ (s->a & s->c) ^ (s->b & s->c));
	s->h = s->g;
	s->g = s->f;
	s->f = s->e;
	s->e = s->d + tmp;
	s->d = s->c;
	s->c = s->b;
	s->b = s->a;
	s->a = tmp + tmp2;
}

static unsigned int	uswap_32(unsigned int x)
{
	return (((((x) & 0xff000000u) >> 24) | (((x) & 0x00ff0000u) >> 8) | \
			(((x) & 0x0000ff00u) << 8) | (((x) & 0x000000ffu) << 24)));
}

static void	main_loop_sha256(t_sha256 *s, unsigned char *msg)
{
	unsigned int	w[64];
	unsigned int	*m;
	unsigned int	s0;
	unsigned int	s1;
	int				i;

	ft_bzero(w, 256);
	m = (unsigned int*)msg;
	i = -1;
	while (++i < 16)
		w[i] = uswap_32(m[i]);
	--i;
	while (++i < 64)
	{
		s0 = rightrotate(w[i - 15], 7) ^ rightrotate(w[i - 15], 18) ^ (w[i - 15] >> 3);
		s1 = rightrotate(w[i - 2], 17) ^ rightrotate(w[i - 2], 19) ^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i-7] + s1;
	}
	s->a = s->out[0];
	s->b = s->out[1];
	s->c = s->out[2];
	s->d = s->out[3];
	s->e = s->out[4];
	s->f = s->out[5];
	s->g = s->out[6];
	s->h = s->out[7];
	i = -1;
	while (++i < 64)
	{
		s->i = i;
		main_loop_sha2562(s, w, &s0, &s1);
	}
}

static char	*get_sha256_hash(unsigned int *h)
{
	char	buff_hex[8][9];
	char	*out;
	int		i;
	int		j;
	int		l;

	i = -1;
	while (++i < 8)
	{
		get_hex(buff_hex[i], h[i], 0);
		reverse_string(buff_hex[i]);
	}
	if (!(out = (char*)malloc(65)))
		ft_exiterror("Malloc failed.", 1);
	i = -1;
	j = -1;
	while (++i < 64)
	{
		if ((!i || i == 8 || i == 16 || i == 24 || i == 32 || i == 40 || \
			i == 48 || i == 56) && (++j + 1))
			l = -1;
		out[i] = buff_hex[j][++l];
	}
	out[i] = '\0';
	return (out);
}

char	*sha256(unsigned char *msg, unsigned long size)
{
	unsigned int	msg_len;
	unsigned int	offset;
	char			*out;
	t_sha256		*s;

	if (!(s = (t_sha256*)malloc(sizeof(struct s_sha256))))
		ft_exiterror("Malloc failed.", 1);
	s->out[0] = 0x6a09e667;
	s->out[1] = 0xbb67ae85;
	s->out[2] = 0x3c6ef372;
	s->out[3] = 0xa54ff53a;
	s->out[4] = 0x510e527f;
	s->out[5] = 0x9b05688c;
	s->out[6] = 0x1f83d9ab;
	s->out[7] = 0x5be0cd19;
	msg_len = fill_message_sha256(&msg, size);
	offset = 0;
	while (offset < msg_len)
	{
		main_loop_sha256(s, (void*)msg + offset);
		s->out[0] += s->a;
		s->out[1] += s->b;
		s->out[2] += s->c;
		s->out[3] += s->d;
		s->out[4] += s->e;
		s->out[5] += s->f;
		s->out[6] += s->g;
		s->out[7] += s->h;
		offset += 64;
	}
	out = get_sha256_hash(s->out);
	free(s);
	return (out);
}