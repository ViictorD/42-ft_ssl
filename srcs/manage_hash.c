/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 22:37:41 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/23 17:04:38 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	manage_s(t_opt *opt, int argc, char **argv, int *i)
{
	unsigned char	*str2;
	char			*str;

	if (*i + 1 == argc)
		opt_error_msg("-s");
	++*i;
	str2 = (unsigned char*)ft_strdup(argv[*i]);
	if (!(str = go_algo(str2, ft_strlen(((char*)str2)))))
	{
		free(str2);
		return ;
	}
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

	--*i;
	while (++*i < argc)
	{
		if ((fd = open(argv[*i], O_RDONLY)) < 0 || fstat(fd, &buff) < 0)
		{
			no_file(argv[*i]);
			continue ;
		}
		if (!(str = (unsigned char*)malloc(buff.st_size + 1)))
			ft_exiterror("Malloc failed.", 1);
		ft_bzero(str, buff.st_size + 1);
		read(fd, str, buff.st_size);
		hash = go_algo(str, buff.st_size);
		print_hash(opt, hash, argv[*i], 0);
		free(hash);
		free(str);
		close(fd);
	}
	++*i;
}

static char	manage_hash2(t_opt *opt, char **argv, int i, char *file)
{
	if (!ft_strcmp("-p", argv[i]))
	{
		stdin(1);
		*file = 1;
	}
	else if (!ft_strcmp("-q", argv[i]))
		opt->q = 1;
	else if (!ft_strcmp("-r", argv[i]))
		opt->r = 1;
	else
		return (0);
	return (1);
}

static char	cmp_algo(char *str)
{
	return (!ft_strcmp("md5", str) \
			|| !ft_strcmp("sha256", str) \
			|| !ft_strcmp("sha224", str) \
			|| !ft_strcmp("sha384", str) \
			|| !ft_strcmp("sha512", str) \
			|| !ft_strcmp("sha512/224", str) \
			|| !ft_strcmp("sha512/256", str));
}

void		manage_hash(t_opt *opt, int argc, char **argv, char algoo)
{
	int		i;
	char	file;

	algo(1, algoo);
	file = 0;
	i = 1;
	if (i + 1 == argc && (file = 1))
		stdin(0);
	while (++i < argc)
	{
		if (manage_hash2(opt, argv, i, &file))
			continue ;
		else if (!ft_strcmp("-s", argv[i]) && (file = 1))
			manage_s(opt, argc, argv, &i);
		else if (*argv[i] == '-' && cmp_algo(argv[1]))
			opt_error_msg(argv[i]);
		else
		{
			read_file(opt, argc, argv, &i);
			file = 1;
		}
	}
	if (!file)
		stdin(0);
}
