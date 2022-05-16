/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:31:53 by yeju              #+#    #+#             */
/*   Updated: 2022/05/13 16:44:41 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

// void	cal_vec(t_info *info)
// {
// 	floor_cast(info);
// 	wall_cast(info);
// 	return ;
// }

// int	raycasting(t_info *info)
// {
// 	cal_vec(info);
// 	draw(info);
// 	return (1);
// }

void	wall_cast(t_info *info, t_wall_data *wall_data, int count)
{
	set_dda(wall_data, info, count);
	init_DDA_cast(wall_data, info);
	stepProgress_until_hit(wall_data, info);
	calc_perp_dist(wall_data, info);
	set_wall_data(wall_data, info);
	set_texture_data(wall_data, info);
	return ;
}

int	raycasting(t_info *info)
{
	t_wall_data	*wall_data;
	int			count;
	int         y;

	wall_data = (t_wall_data *)malloc(sizeof(t_wall_data));
	if (!wall_data)
		return (0);
	utils_bzero(wall_data, sizeof(t_wall_data));
	count = -1;
	while (++count < info->win_wid)
	{
		wall_cast(info, wall_data, count);
		y = wall_data->draw_start - 1;
		while (++y < wall_data->draw_end)
			info->buf[y][count] = set_color(wall_data, info);
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img->img, 0, 0);
	draw(info);
	free(wall_data);
	return (1);
}

void	hook_set(t_info *info)
{
	mlx_hook(info->win, X_KEY_PRESS, 0, key_press, info);
	mlx_hook(info->win, X_KEY_RELEASE, 0, key_release, info);
	mlx_hook(info->win, X_CLICK_EXIT, 0, close_win, info);
	mlx_loop_hook(info->mlx, render, info);
	mlx_loop(info->mlx);
}
