/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 20:01:16 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/22 22:19:30 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static unsigned long g_k[80] = {0x428a2f98d728ae22, 0x7137449123ef65cd,
	0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538,
	0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c,
	0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
	0x9bdc06a725c71235, 0xc19bf174cf692694, 0xe49b69c19ef14ad2,
	0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4,
	0x76f988da831153b5, 0x983e5152ee66dfab, 0xa831c66d2db43210,
	0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2,
	0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
	0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed,
	0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8,
	0x81c2c92e47edaee6, 0x92722c851482353b, 0xa2bfe8a14cf10364,
	0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
	0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a,
	0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63,
	0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
	0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72,
	0x8cc702081a6439ec, 0x90befffa23631e28, 0xa4506cebde82bde9,
	0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c,
	0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae,
	0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493,
	0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c, 0x4cc5d4becb3e42b6,
	0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817};

unsigned long	rrot_l(unsigned long x, unsigned long c)
{
	return ((x >> c) | (x << (64 - c)));
}

static void	main_loop_sha5122(t_sha512 *s, unsigned long *w, unsigned int *s0, \
				unsigned int *s1)
{
	unsigned long	ch;
	unsigned long	tmp;
	unsigned long	tmp2;


	*s1 = rrot_l(s->e, 14) ^ rrot_l(s->e, 18) ^ rrot_l(s->e, 41);
	ch = (s->e & s->f) ^ ((~s->e) & s->g);
	tmp = s->h + *s1 + ch + g_k[s->i] + w[s->i];
	*s0 = rrot_l(s->a, 28) ^ rrot_l(s->a, 34) ^ rrot_l(s->a, 39);
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

static char	*get_sha512_hash(unsigned long *h)
{
	char	buff_hex[16][9];
	char	*out;
	int		i;
	int		j;
	int		l;

	i = -1;
	while (++i < 16)
	{
		get_hex(buff_hex[i], h[i], 0);
		reverse_string(buff_hex[i]);
	}
	if (!(out = (char*)malloc(129)))
		ft_exiterror("Malloc failed.", 1);
	i = -1;
	j = -1;
	while (++i < 128)
	{
		if ((!i || i == 8 || i == 16 || i == 24 || i == 32 || i == 40 || \
			i == 48 || i == 56 || i == 64 || i == 72 || i == 80 || i == 88 || \
			i == 96 || i == 104 || i == 112 || i == 120) && (++j + 1))
			l = -1;
		out[i] = buff_hex[j][++l];
	}
	out[i] = '\0';
	return (out);
}

static void	asign_letter(t_sha512 *s)
{
	s->a = s->out[0];
	s->b = s->out[1];
	s->c = s->out[2];
	s->d = s->out[3];
	s->e = s->out[4];
	s->f = s->out[5];
	s->g = s->out[6];
	s->h = s->out[7];
}

unsigned long			uswap_64(unsigned long x)
{
	return ((((x) & 0xff00000000000000ull) >> 56) \
		| (((x) & 0x00ff000000000000ull) >> 40) \
		| (((x) & 0x0000ff0000000000ull) >> 24) \
		| (((x) & 0x000000ff00000000ull) >> 8) \
		| (((x) & 0x00000000ff000000ull) << 8) \
		| (((x) & 0x0000000000ff0000ull) << 24) \
		| (((x) & 0x000000000000ff00ull) << 40) \
		| (((x) & 0x00000000000000ffull) << 56));
}

static void	main_loop_sha512(t_sha512 *s, unsigned char *msg)
{
	unsigned long	w[80];
	unsigned long	*m;
	unsigned int	s0;
	unsigned int	s1;
	int				i;

	ft_bzero(w, 640);
	m = (unsigned long*)msg;
	i = -1;
	while (++i < 16)
		w[i] = uswap_64(m[i]);
	--i;
	while (++i < 80)
	{
		s0 = rrot_l(w[i - 15], 1) ^ rrot_l(w[i - 15], 8) ^ (w[i - 15] >> 7);
		s1 = rrot_l(w[i - 2], 19) ^ rrot_l(w[i - 2], 61) ^ (w[i - 2] >> 6);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}
	asign_letter(s);
	i = -1;
	while (++i < 80)
	{
		s->i = i;
		main_loop_sha5122(s, w, &s0, &s1);
	}
}

static size_t	fill_message_sha512(unsigned char **msg, unsigned long len)
{
	unsigned long	mod;
	unsigned char	*buff;

	mod = 128 + (128 * (len / 128)) - len;
	if (mod < 17)
		mod += 128;
	if (!(buff = (unsigned char*)malloc(len + mod)))
		ft_exiterror("Malloc failed", 1);
	ft_memcpy(buff, *msg, len);
	buff[len] = 0x80;
	ft_bzero(buff + len + 1, mod - 1);
	// buff[len + mod - 16] = (char)((len * 8) >> (8 * 15));
	// buff[len + mod - 15] = (char)((len * 8) >> (8 * 14));
	// buff[len + mod - 14] = (char)((len * 8) >> (8 * 13));
	// buff[len + mod - 13] = (char)((len * 8) >> (8 * 12));
	// buff[len + mod - 12] = (char)((len * 8) >> (8 * 11));
	// buff[len + mod - 11] = (char)((len * 8) >> (8 * 10));
	// buff[len + mod - 10] = (char)((len * 8) >> (8 * 9));
	// buff[len + mod - 9] = (char)((len * 8) >> (8 * 8));
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

char		*sha512(unsigned char *msg, unsigned long size)
{
	unsigned int	msg_len;
	unsigned int	offset;
	char			*out;
	t_sha512		*s;

	if (!(s = (t_sha512*)malloc(sizeof(struct s_sha512))))
		ft_exiterror("Malloc failed.", 1);
	init_sha512_output(s);
	msg_len = fill_message_sha512(&msg, size);
	offset = 0;
	while (offset < msg_len)
	{
		main_loop_sha512(s, (void*)msg + offset);
		add_to_h_512(s);
		offset += 128;
	}
	out = get_sha512_hash(s->out);
	free(s);
	free(msg);
	return (out);
}
