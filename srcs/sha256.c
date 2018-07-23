/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 18:11:33 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/23 17:15:48 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static unsigned int g_k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,
	0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138,
	0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624,
	0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f,
	0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

static void	main_loop_sha2562(t_sha256 *s, unsigned int *w, unsigned int *s0, \
				unsigned int *s1)
{
	unsigned int	ch;
	unsigned int	tmp;
	unsigned int	tmp2;

	*s1 = rrot(s->e, 6) ^ rrot(s->e, 11) ^ rrot(s->e, 25);
	ch = (s->e & s->f) ^ ((~s->e) & s->g);
	tmp = s->h + *s1 + ch + g_k[s->i] + w[s->i];
	*s0 = rrot(s->a, 2) ^ rrot(s->a, 13) ^ rrot(s->a, 22);
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

static char	*get_sha256_hash(unsigned int *h)
{
	unsigned char	buff_hex[8][8];
	char			*out;
	int				i;
	int				j;
	int				l;

	i = -1;
	while (++i < 8)
	{
		ft_memset(buff_hex[i], '0', 8);
		get_hex(buff_hex[i], h[i], 0);
		strrev(buff_hex[i], 8);
	}
	if (!(out = (char*)malloc(65)))
		ft_exiterror("Malloc failed.", 1);
	i = -1;
	j = -1;
	while (++i < 64)
	{
		if (!(i % 8) && (++j + 1))
			l = -1;
		out[i] = buff_hex[j][++l];
	}
	out[i] = '\0';
	return (out);
}

void		main_loop_sha256(t_sha256 *s, unsigned char *msg)
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
		s0 = rrot(w[i - 15], 7) ^ rrot(w[i - 15], 18) ^ (w[i - 15] >> 3);
		s1 = rrot(w[i - 2], 17) ^ rrot(w[i - 2], 19) ^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}
	asign_letter_256(s);
	i = -1;
	while (++i < 64)
	{
		s->i = i;
		main_loop_sha2562(s, w, &s0, &s1);
	}
}

size_t		fill_message_sha256(unsigned char **msg, unsigned long len)
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

char		*sha256(unsigned char *msg, unsigned long size)
{
	unsigned int	msg_len;
	unsigned int	offset;
	char			*out;
	t_sha256		*s;

	if (!(s = (t_sha256*)malloc(sizeof(struct s_sha256))))
		ft_exiterror("Malloc failed.", 1);
	init_sha2_output(s, SHA256);
	msg_len = fill_message_sha256(&msg, size);
	offset = 0;
	while (offset < msg_len)
	{
		main_loop_sha256(s, (void*)msg + offset);
		add_to_h(s);
		offset += 64;
	}
	out = get_sha256_hash(s->out);
	free(s);
	free(msg);
	return (out);
}
