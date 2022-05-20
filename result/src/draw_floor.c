/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:11:19 by yeju              #+#    #+#             */
/*   Updated: 2022/05/20 11:11:31 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void	draw(t_info *info)
{
	int	y;
	int	x;

	y = -1;
	while (++y < info->win_hei)
	{
		x = -1;
		while (++x < info->win_wid)
			info->img->data[y * info->win_wid + x] = info->buf[x][y];
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img->img, 0, 0);
}
