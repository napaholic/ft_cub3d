/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:12:58 by yeju              #+#    #+#             */
/*   Updated: 2022/05/22 12:10:41 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	utils_white_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || \
		c == '\f' || c == ' ')
		return (1);
	return (0);
}

int	utils_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

int	utils_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	utils_bzero(void *s, size_t n)
{
	char	*dest;
	size_t	i;

	dest = s;
	i = 0;
	while (i++ < n)
		*dest++ = 0;
}

void	set_arr(int *dx, int *dy)
{
	dx[0] = 1;
	dx[1] = 1;
	dx[2] = 0;
	dx[3] = -1;
	dx[4] = -1;
	dx[5] = -1;
	dx[6] = 0;
	dx[7] = 1;
	dy[0] = 0;
	dy[1] = 1;
	dy[2] = 1;
	dy[3] = 1;
	dy[4] = 0;
	dy[5] = -1;
	dy[6] = -1;
	dy[7] = -1;
	return ;
}
