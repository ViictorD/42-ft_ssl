/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 20:01:16 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/23 17:31:38 by vdarmaya         ###   ########.fr       */
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

static void	main_loop_sha5122(t_sha512 *s, unsigned long *w, \
				unsigned long *s0, unsigned long *s1)
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

void		main_loop_sha512(t_sha512 *s, unsigned char *msg)
{
	unsigned long	w[80];
	unsigned long	*m;
	unsigned long	s0;
	unsigned long	s1;
	int				i;

	ft_bzero(w, 640);
	m = (unsigned long*)msg;
	i = -1;
	while (++i < 16)
		w[i] = m[i];
	--i;
	while (++i < 80)
	{
		s0 = rrot_l(w[i - 15], 1) ^ rrot_l(w[i - 15], 8) ^ (w[i - 15] >> 7);
		s1 = rrot_l(w[i - 2], 19) ^ rrot_l(w[i - 2], 61) ^ (w[i - 2] >> 6);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}
	asign_letter_512(s);
	i = -1;
	while (++i < 80)
	{
		s->i = i;
		main_loop_sha5122(s, w, &s0, &s1);
	}
}

static void	add_size_64(unsigned char *buff, __uint128_t len, __uint128_t mod)
{
	buff[len + mod - 1] = ((len * 8) & 0xFF00000000000000) >> 56;
	buff[len + mod - 2] = ((len * 8) & 0x00FF000000000000) >> 48;
	buff[len + mod - 3] = ((len * 8) & 0x0000FF0000000000) >> 40;
	buff[len + mod - 4] = ((len * 8) & 0x000000FF00000000) >> 32;
	buff[len + mod - 5] = ((len * 8) & 0x00000000FF000000) >> 24;
	buff[len + mod - 6] = ((len * 8) & 0x0000000000FF0000) >> 16;
	buff[len + mod - 7] = ((len * 8) & 0x000000000000FF00) >> 8;
	buff[len + mod - 8] = ((len * 8) & 0x00000000000000FF);
	buff[len + mod - 9] = ((len * 8) >> 64 & 0xFF00000000000000) >> 56;
	buff[len + mod - 10] = ((len * 8) >> 64 & 0x00FF000000000000) >> 48;
	buff[len + mod - 11] = ((len * 8) >> 64 & 0x0000FF0000000000) >> 40;
	buff[len + mod - 12] = ((len * 8) >> 64 & 0x000000FF00000000) >> 32;
	buff[len + mod - 13] = ((len * 8) >> 64 & 0x00000000FF000000) >> 24;
	buff[len + mod - 14] = ((len * 8) >> 64 & 0x0000000000FF0000) >> 16;
	buff[len + mod - 15] = ((len * 8) >> 64 & 0x000000000000FF00) >> 8;
	buff[len + mod - 16] = ((len * 8) >> 64 & 0x00000000000000FF);
}

size_t		fill_message_sha512(unsigned char **msg, __uint128_t len)
{
	__uint128_t		mod;
	unsigned char	*buff;

	mod = 128 + (128 * (len / 128)) - len;
	if (mod < 17)
		mod += 128;
	if (!(buff = (unsigned char*)malloc(len + mod)))
		ft_exiterror("Malloc failed", 1);
	ft_memcpy(buff, *msg, len);
	buff[len] = 0x80;
	ft_bzero(buff + len + 1, mod - 1);
	add_size_64(buff, len, mod);
	rev_64(buff, len);
	*msg = buff;
	return (mod + len);
}

char		*sha512(unsigned char *msg, __uint128_t size)
{
	unsigned int	msg_len;
	unsigned int	offset;
	char			*out;
	t_sha512		*s;

	if (!(s = (t_sha512*)malloc(sizeof(struct s_sha512))))
		ft_exiterror("Malloc failed.", 1);
	init_sha512_output(s, SHA512);
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
