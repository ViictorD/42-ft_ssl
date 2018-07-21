/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 20:45:59 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/16 20:47:23 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_hash(t_opt *opt, char *str, char *str2, char quot)
{
	if (!opt->q && !opt->r)
	{
		ft_putstr("MD5 (");
		if (quot)
			ft_putchar('\"');
		ft_putstr(str2);
		if (quot)
			ft_putchar('\"');
		ft_putstr(") = ");
		ft_putendl(str);
	}
	else if (!opt->q && opt->r)
	{
		ft_putstr(str);
		ft_putchar(' ');
		if (quot)
			ft_putchar('\"');
		ft_putstr(str2);
		if (quot)
			ft_putchar('\"');
		ft_putchar('\n');
	}
	else
		ft_putendl(str);
}
