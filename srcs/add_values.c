/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:14:40 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/23 17:33:09 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	add_to_h(t_sha256 *s)
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

void	add_to_h_512(t_sha512 *s)
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

void	asign_letter_256(t_sha256 *s)
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

void	asign_letter_512(t_sha512 *s)
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
