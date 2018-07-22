/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:59:08 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/22 18:13:57 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	*get_sha224_hash(unsigned int *h)
{
	char	buff_hex[7][9];
	char	*out;
	int		i;
	int		j;
	int		l;

	i = -1;
	while (++i < 7)
	{
		get_hex(buff_hex[i], h[i], 0);
		reverse_string(buff_hex[i]);
	}
	if (!(out = (char*)malloc(57)))
		ft_exiterror("Malloc failed.", 1);
	i = -1;
	j = -1;
	while (++i < 56)
	{
		if ((!i || i == 8 || i == 16 || i == 24 || i == 32 || i == 40 || \
			i == 48) && (++j + 1))
			l = -1;
		out[i] = buff_hex[j][++l];
	}
	out[i] = '\0';
	return (out);
}

char		*sha224(unsigned char *msg, unsigned long size)
{
	unsigned int	msg_len;
	unsigned int	offset;
	char			*out;
	t_sha256		*s;

	if (!(s = (t_sha256*)malloc(sizeof(struct s_sha256))))
		ft_exiterror("Malloc failed.", 1);
	init_sha2_output(s, SHA224);
	msg_len = fill_message_sha256(&msg, size);
	offset = 0;
	while (offset < msg_len)
	{
		main_loop_sha256(s, (void*)msg + offset);
		add_to_h(s);
		offset += 64;
	}
	out = get_sha224_hash(s->out);
	free(s);
	free(msg);
	return (out);
}
