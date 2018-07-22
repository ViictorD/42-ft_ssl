/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:51:17 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/22 21:23:26 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			init_sha2_output(t_sha256 *s, char algo)
{
	if (algo == SHA256)
	{
		s->out[0] = 0x6a09e667;
		s->out[1] = 0xbb67ae85;
		s->out[2] = 0x3c6ef372;
		s->out[3] = 0xa54ff53a;
		s->out[4] = 0x510e527f;
		s->out[5] = 0x9b05688c;
		s->out[6] = 0x1f83d9ab;
		s->out[7] = 0x5be0cd19;
	}
	else if (algo == SHA224)
	{
		s->out[0] = 0xc1059ed8;
		s->out[1] = 0x367cd507;
		s->out[2] = 0x3070dd17;
		s->out[3] = 0xf70e5939;
		s->out[4] = 0xffc00b31;
		s->out[5] = 0x68581511;
		s->out[6] = 0x64f98fa7;
		s->out[7] = 0xbefa4fa4;
	}
}

void			init_sha512_output(t_sha512 *s)
{
	s->out[0] = 0x6a09e667f3bcc908;
	s->out[1] = 0xbb67ae8584caa73b;
	s->out[2] = 0x3c6ef372fe94f82b;
	s->out[3] = 0xa54ff53a5f1d36f1;
	s->out[4] = 0x510e527fade682d1;
	s->out[5] = 0x9b05688c2b3e6c1f;
	s->out[6] = 0x1f83d9abfb41bd6b;
	s->out[7] = 0x5be0cd19137e2179;
}

void			add_to_h(t_sha256 *s)
{
	s->out[0] += s->a;
	s->out[1] += s->b;
	s->out[2] += s->c;
	s->out[3] += s->d;
	s->out[4] += s->e;
	s->out[5] += s->f;
	s->out[6] += s->g;
	s->out[7] += s->h;
}

void			add_to_h_512(t_sha512 *s)
{
	s->out[0] += s->a;
	s->out[1] += s->b;
	s->out[2] += s->c;
	s->out[3] += s->d;
	s->out[4] += s->e;
	s->out[5] += s->f;
	s->out[6] += s->g;
	s->out[7] += s->h;
}

unsigned int	uswap_32(unsigned int x)
{
	return (((((x) & 0xff000000u) >> 24) | (((x) & 0x00ff0000u) >> 8) | \
			(((x) & 0x0000ff00u) << 8) | (((x) & 0x000000ffu) << 24)));
}

char			*go_algo(unsigned char *str, size_t len)
{
	char	*hash;

	if (algo(0, 0) == MD5)
		hash = md5(str, len);
	else if (algo(0, 0) == SHA256)
		hash = sha256(str, len);
	else if (algo(0, 0) == SHA224)
		hash = sha224(str, len);
	else if (algo(0, 0) == SHA512)
		hash = sha512(str, len);
	else
		return (NULL);
	return (hash);
}
