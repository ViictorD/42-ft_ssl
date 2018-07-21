/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 20:53:02 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/21 19:43:25 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	manage_opt(char **argv, t_opt *opt)
{
	if (!ft_strcmp("md5", argv[1]) || !ft_strcmp("sha256", argv[1]))
		opt->algo = argv[1];
	else
	{
		ft_fputstr("ft_ssl: Error:'", 2);
		ft_fputstr(argv[1], 2);
		ft_fputstr("'is an invalid command.\n\nStandard commands:\n\n", 2);
		ft_exiterror("Message Digest commands:\n\nmd5\nsha256", 1);
	}
}

void		opt_error_msg(char *param)
{
	ft_fputstr("ft_ssl: Error:'", 2);
	ft_fputstr(param, 2);
	ft_fputstr("'is an invalid option.\n\noptions are\n\n", 2);
	ft_fputstr("-p\t\techo STDIN to STDOUT and append the checksum ", 2);
	ft_fputstr("to STDOUT\n", 2);
	ft_fputstr("-q\t\tquiet mode\n", 2);
	ft_fputstr("-r\t\treverse the format of the output\n", 2);
	ft_fputstr("-s [string]\tprint the sum of the given string\n", 2);
	exit(1);
}

int			main(int argc, char **argv)
{
	t_opt	*opt;

	if (argc < 2)
		ft_exiterror("usage: ft_ssl command [command opts] [command args]", 1);
	if (!(opt = (t_opt*)malloc(sizeof(t_opt))))
		ft_exiterror("Malloc failed.", 1);
	opt->q = 0;
	opt->r = 0;
	manage_opt(argv, opt);
	if (!ft_strcmp("md5", argv[1]))
		manage_md5(opt, argc, argv);
	if (!ft_strcmp("sha256", argv[1]))
		ft_putstr(sha256(argv[2], ft_strlen(argv[2])));
	return (0);
}
