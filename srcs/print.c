/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 20:45:59 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/23 16:52:07 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	print_normal(char *str, char *str2, char quot)
{
	if (algo(0, 0) == MD5)
		ft_putstr("MD5 (");
	else if (algo(0, 0) == SHA224)
		ft_putstr("SHA224 (");
	else if (algo(0, 0) == SHA256)
		ft_putstr("SHA256 (");
	else if (algo(0, 0) == SHA384)
		ft_putstr("SHA384 (");
	else if (algo(0, 0) == SHA512)
		ft_putstr("SHA512 (");
	else if (algo(0, 0) == SHA512224)
		ft_putstr("SHA512/224 (");
	else if (algo(0, 0) == SHA512256)
		ft_putstr("SHA512/256 (");
	if (quot)
		ft_putchar('\"');
	ft_putstr(str2);
	if (quot)
		ft_putchar('\"');
	ft_putstr(") = ");
	ft_putendl(str);
}

void		print_hash(t_opt *opt, char *str, char *str2, char quot)
{
	if (!opt->q && !opt->r)
		print_normal(str, str2, quot);
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

void		no_file(char *name)
{
	ft_fputstr("ft_ssl: ", 2);
	ft_fputstr(name, 2);
	ft_fputstr(": No such file or directory\n", 2);
}
