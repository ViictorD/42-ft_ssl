/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:51:17 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/23 17:14:53 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char			*go_algo(unsigned char *str, size_t len)
{
	char	*hash;

	if (algo(0, 0) == MD5)
		hash = md5(str, len);
	else if (algo(0, 0) == SHA256)
		hash = sha256(str, len);
	else if (algo(0, 0) == SHA224)
		hash = sha224(str, len);
	else if (algo(0, 0) == SHA384)
		hash = sha384(str, len);
	else if (algo(0, 0) == SHA512)
		hash = sha512(str, len);
	else if (algo(0, 0) == SHA512224)
		hash = sha512t(str, len, SHA512224);
	else if (algo(0, 0) == SHA512256)
		hash = sha512t(str, len, SHA512256);
	else
		return (NULL);
	return (hash);
}
