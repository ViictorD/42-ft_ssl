/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_md5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 22:37:41 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/16 20:46:06 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	md5_stdin2(char **save, char **str, int ret)
{
	char			*tmp;

	tmp = *save;
	*save = ft_strjoin(*save, *str);
	free(tmp);
	free(*str);
	if (ret == 2)
	{
		tmp = *save;
		*save = ft_strjoin(*save, "\n");
		free(tmp);
	}
}

static void	md5_stdin(char p)
{
	char			*save;
	unsigned char	*usave;
	char			*str;
	int				ret;

	str = NULL;
	save = ft_strdup("");
	while ((ret = fake_gnl(0, &str, 0)) > 0)
		md5_stdin2(&save, &str, ret);
	free(str);
	if (p)
		ft_putstr(save);
	usave = (unsigned char*)save;
	str = md5(&usave, ft_strlen(save));
	ft_putstr(str);
	free(str);
	free(usave);
}

static void	manage_s(t_opt *opt, int argc, char **argv, int *i)
{
	unsigned char	*str2;
	char			*str;

	if (*i + 1 == argc)
		opt_error_msg("-s");
	++*i;
	str2 = (unsigned char*)ft_strdup(argv[*i]);
	str = md5(&str2, ft_strlen((char*)str2));
	free(str2);
	print_hash(opt, str, argv[*i], 1);
	free(str);
}

static void	read_file(t_opt *opt, int argc, char **argv, int *i)
{
	int				fd;
	struct stat		buff;
	unsigned char	*str;
	char			*hash;

	while (++*i < argc)
	{
		if ((fd = open(argv[*i], O_RDONLY)) < 0 || fstat(fd, &buff) < 0)
		{
			ft_fputstr("ft_ssl: ", 2);
			ft_fputstr(argv[*i], 2);
			ft_fputstr(": No such file or directory\n", 2);
			continue ;
		}
		if (!(str = (unsigned char*)malloc(buff.st_size + 1)))
			ft_exiterror("Malloc failed.", 1);
		ft_bzero(str, buff.st_size + 1);
		read(fd, str, buff.st_size);
		hash = md5(&str, buff.st_size);
		print_hash(opt, hash, argv[*i], 0);
		free(hash);
		free(str);
		close(fd);
	}
}

void		manage_md5(t_opt *opt, int argc, char **argv)
{
	int		i;

	i = 1;
	if (i + 1 == argc)
		md5_stdin(0);
	while (++i < argc)
	{
		if (!ft_strcmp("-p", argv[i]))
			md5_stdin(1);
		else if (!ft_strcmp("-s", argv[i]))
			manage_s(opt, argc, argv, &i);
		else if (!ft_strcmp("-q", argv[i]))
			opt->q = 1;
		else if (!ft_strcmp("-r", argv[i]))
			opt->r = 1;
		else if (*argv[i] == '-' && (!ft_strcmp("md5", argv[1]) || \
			!ft_strcmp("sha256", argv[1])))
			opt_error_msg(argv[i]);
		else
		{
			--i;
			read_file(opt, argc, argv, &i);
			++i;
		}
	}
}
