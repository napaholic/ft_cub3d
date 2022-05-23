/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:12:58 by yeju              #+#    #+#             */
/*   Updated: 2022/05/20 11:33:23 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

char	*ft_strstr(char *ap_str, char *ap_find_str)
{
	char	*pos;
	char	*find_pos;

	while (*ap_str != 0)
	{
		if (*ap_str == *ap_find_str)
		{
			pos = ap_str + 1;
			find_pos = ap_find_str + 1;
			while (*find_pos != 0 && *pos != 0 && *pos == *find_pos)
			{
				pos++;
				find_pos++;
			}
			if (*find_pos == 0)
				return ((char *)ap_str);
			if (*pos == 0)
				break ;
		}
		ap_str++;
	}
	return ((char *)0);
}
