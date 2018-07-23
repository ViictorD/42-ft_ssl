/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512t.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 16:15:07 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/23 17:32:39 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	init_sha_512224_output(t_sha512 *s)
{
	s->out[0] = 0x8C3D37C819544DA2;
	s->out[1] = 0x73E1996689DCD4D6;
	s->out[2] = 0x1DFAB7AE32FF9C82;
	s->out[3] = 0x679DD514582F9FCF;
	s->out[4] = 0x0F6D2B697BD44DA8;
	s->out[5] = 0x77E36F7304C48942;
	s->out[6] = 0x3F9D85A86A1D36C8;
	s->out[7] = 0x1112E6AD91D692A1;
}

static void	init_sha_512256_output(t_sha512 *s)
{
	s->out[0] = 0x22312194FC2BF72C;
	s->out[1] = 0x9F555FA3C84C64C2;
	s->out[2] = 0x2393B86B6F53B151;
	s->out[3] = 0x963877195940EABD;
	s->out[4] = 0x96283EE2A88EFFE3;
	s->out[5] = 0xBE5E1E2553863992;
	s->out[6] = 0x2B0199FC2C85B8AA;
	s->out[7] = 0x0EB72DDC81C52CA2;
}

static void	trunc_str(char **str, char algo)
{
	char	*new;
	int		size;

	size = 0;
	if (algo == SHA512224)
		size = 28 * 2;
	else if (algo == SHA512256)
		size = 32 * 2;
	if (!(new = (char*)malloc(size + 1)))
		ft_exiterror("Malloc failed.", 1);
	ft_memcpy(new, *str, size);
	new[size] = '\0';
	free(*str);
	*str = new;
}

char		*sha512t(unsigned char *msg, __uint128_t size, char algo)
{
	unsigned int	msg_len;
	unsigned int	offset;
	char			*out;
	t_sha512		*s;

	if (!(s = (t_sha512*)malloc(sizeof(struct s_sha512))))
		ft_exiterror("Malloc failed.", 1);
	if (algo == SHA512224)
		init_sha_512224_output(s);
	else if (algo == SHA512256)
		init_sha_512256_output(s);
	msg_len = fill_message_sha512(&msg, size);
	offset = 0;
	while (offset < msg_len)
	{
		main_loop_sha512(s, (void*)msg + offset);
		add_to_h_512(s);
		offset += 128;
	}
	out = get_sha512_hash(s->out);
	trunc_str(&out, algo);
	free(s);
	free(msg);
	return (out);
}
