/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_hash2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:04:25 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/23 17:04:42 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	stdin2(char **save, char **str, int ret)
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

void		stdin(char p)
{
	char			*save;
	unsigned char	*usave;
	char			*str;
	int				ret;

	str = NULL;
	save = ft_strdup("");
	while ((ret = fake_gnl(0, &str, 0)) > 0)
		stdin2(&save, &str, ret);
	free(str);
	if (p)
		ft_putstr(save);
	usave = (unsigned char*)save;
	if (!(str = go_algo(usave, ft_strlen((char*)usave))))
	{
		free(usave);
		return ;
	}
	ft_putstr(str);
	free(str);
	free(usave);
}
