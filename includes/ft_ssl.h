/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 20:54:06 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/21 19:45:05 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>

# define INIT_DATA_A 0x67452301
# define INIT_DATA_B 0xefcdab89
# define INIT_DATA_C 0x98badcfe
# define INIT_DATA_D 0x10325476

typedef struct		s_data
{
	unsigned int	out[4];
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;
}					t_data;

typedef struct		s_sha256
{
	unsigned int	out[8];
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;
	unsigned int	e;
	unsigned int	f;
	unsigned int	g;
	unsigned int	h;
	int				i;
}					t_sha256;

typedef struct		s_opt
{
	char			*algo;
	char			q;
	char			r;
}					t_opt;

char				*md5(unsigned char **content, unsigned long size);
unsigned int		leftrotate(unsigned int x, unsigned int c);
unsigned int		rightrotate(unsigned int x, unsigned int c);
void				manage_md5(t_opt *opt, int argc, char **argv);
void				opt_error_msg(char *param);
void				get_hex(char *buff, unsigned int c, int i);
unsigned int		convert_little_endiant(unsigned int num);
void				reverse_string(char *str);
void				print_hash(t_opt *opt, char *str, char *str2, char quot);
char				*sha256(unsigned char *msg, unsigned long size);

#endif