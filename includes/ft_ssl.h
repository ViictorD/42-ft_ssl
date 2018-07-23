/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 20:54:06 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/23 17:31:36 by vdarmaya         ###   ########.fr       */
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

# define MD5		1
# define SHA224		2
# define SHA256		3
# define SHA384		4
# define SHA512		5
# define SHA512224	6
# define SHA512256	7

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

typedef struct		s_sha512
{
	unsigned long	out[8];
	unsigned long	a;
	unsigned long	b;
	unsigned long	c;
	unsigned long	d;
	unsigned long	e;
	unsigned long	f;
	unsigned long	g;
	unsigned long	h;
	int				i;
}					t_sha512;

typedef struct		s_opt
{
	char			*algo;
	char			q;
	char			r;
}					t_opt;

char				*md5(unsigned char *content, unsigned long size);
char				*sha224(unsigned char *msg, unsigned long size);
char				*sha256(unsigned char *msg, unsigned long size);
char				*sha384(unsigned char *msg, __uint128_t size);
char				*sha512(unsigned char *msg, __uint128_t size);
char				*sha512t(unsigned char *msg, __uint128_t size, char algo);
unsigned int		leftrotate(unsigned int x, unsigned int c);
unsigned int		rrot(unsigned int x, unsigned int c);
unsigned long		rrot_l(unsigned long x, unsigned long c);
void				manage_hash(t_opt *opt, int argc, char **argv, char algoo);
void				opt_error_msg(char *param);
void				get_hex(unsigned char *buff, unsigned long c, int i);
unsigned int		convert_little_endiant(unsigned int num);
void				print_hash(t_opt *opt, char *str, char *str2, char quot);
void				stdin(char p);
char				algo(char set, char value);
void				no_file(char *name);
void				init_sha2_output(t_sha256 *s, char algo);
size_t				fill_message_sha256(unsigned char **msg, unsigned long len);
void				main_loop_sha256(t_sha256 *s, unsigned char *msg);
unsigned int		uswap_32(unsigned int x);
void				add_to_h(t_sha256 *s);
char				*go_algo(unsigned char *str, size_t len);
void				init_sha512_output(t_sha512 *s, char algo);
void				add_to_h_512(t_sha512 *s);
void				strrev(unsigned char *str, unsigned long len);
size_t				fill_message_sha512(unsigned char **msg, __uint128_t len);
void				main_loop_sha512(t_sha512 *s, unsigned char *msg);
char				*get_sha512_hash(unsigned long *h);
void				asign_letter_256(t_sha256 *s);
void				asign_letter_512(t_sha512 *s);
void				rev_64(unsigned char *str, unsigned long len);

#endif
