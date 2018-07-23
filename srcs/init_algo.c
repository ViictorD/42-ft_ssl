/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:13:30 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/23 17:14:02 by vdarmaya         ###   ########.fr       */
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

void			init_sha512_output(t_sha512 *s, char algo)
{
	if (algo == SHA384)
	{
		s->out[0] = 0xcbbb9d5dc1059ed8;
		s->out[1] = 0x629a292a367cd507;
		s->out[2] = 0x9159015a3070dd17;
		s->out[3] = 0x152fecd8f70e5939;
		s->out[4] = 0x67332667ffc00b31;
		s->out[5] = 0x8eb44a8768581511;
		s->out[6] = 0xdb0c2e0d64f98fa7;
		s->out[7] = 0x47b5481dbefa4fa4;
	}
	else if (algo == SHA512)
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
}
