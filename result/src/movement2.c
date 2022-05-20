/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:12:58 by yeju              #+#    #+#             */
/*   Updated: 2022/05/20 11:20:54 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	rotate_right(t_info *info)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = info->pos->dir_x;
	info->pos->dir_x = info->pos->dir_x * cos(-info->pos->rot_speed) - \
		info->pos->dir_y * sin(-info->pos->rot_speed);
	info->pos->dir_y = old_dir_x * sin(-info->pos->rot_speed) + \
		info->pos->dir_y * cos(-info->pos->rot_speed);
	old_plane_x = info->pos->plane_x;
	info->pos->plane_x = info->pos->plane_x * cos(-info->pos->rot_speed) - \
		info->pos->plane_y * sin(-info->pos->rot_speed);
	info->pos->plane_y = old_plane_x * sin(-info->pos->rot_speed) + \
		info->pos->plane_y * cos(-info->pos->rot_speed);
	return (1);
}

int	key_update(t_info *info)
{
	if (info->key->w == 1)
		return (player_move_front(info));
	if (info->key->a == 1)
		return (player_move_left(info));
	if (info->key->s == 1)
		return (player_move_back(info));
	if (info->key->d == 1)
		return (player_move_right(info));
	if (info->key->left == 1)
		return (rotate_right(info));
	if (info->key->right == 1)
		return (rotate_left(info));
	if (info->key->e == 1)
		return (rotate_mouse(info));
	return (0);
}
