/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 15:40:51 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/23 17:18:12 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	*get_sha384_hash(unsigned long *h)
{
	unsigned char	buff_hex[6][16];
	char			*out;
	int				i;
	int				j;
	int				l;

	i = -1;
	while (++i < 6)
	{
		ft_memset(buff_hex[i], '0', 16);
		get_hex(buff_hex[i], h[i], 0);
		strrev(buff_hex[i], 16);
	}
	if (!(out = (char*)malloc(97)))
		ft_exiterror("Malloc failed.", 1);
	i = -1;
	j = -1;
	while (++i < 96)
	{
		if (!(i % 16) && (++j + 1))
			l = -1;
		out[i] = buff_hex[j][++l];
	}
	out[i] = '\0';
	return (out);
}

char		*sha384(unsigned char *msg, __uint128_t size)
{
	unsigned int	msg_len;
	unsigned int	offset;
	char			*out;
	t_sha512		*s;

	if (!(s = (t_sha512*)malloc(sizeof(struct s_sha512))))
		ft_exiterror("Malloc failed.", 1);
	init_sha512_output(s, SHA384);
	msg_len = fill_message_sha512(&msg, size);
	offset = 0;
	while (offset < msg_len)
	{
		main_loop_sha512(s, (void*)msg + offset);
		add_to_h_512(s);
		offset += 128;
	}
	out = get_sha384_hash(s->out);
	free(s);
	free(msg);
	return (out);
}
