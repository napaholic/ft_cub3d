/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:59:50 by yeju              #+#    #+#             */
/*   Updated: 2022/05/13 16:46:49 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	player_move_front(t_info *info)
{
	double	mvx;
	double	mvy;

	mvx = info->pos->dir_x * info->pos->move_speed;
	mvy = info->pos->dir_y * info->pos->move_speed;
	if (info->map->world_map[(int)info->pos->pos_y][(int)(info->pos->pos_x + mvx)] == '0')
	{
		info->pos->pos_x += mvx;
	}
	if (info->map->world_map[(int)(info->pos->pos_y + mvy)][(int)info->pos->pos_x] == '0')
	{
		info->pos->pos_y += mvy;
	}
	return (1);
}

int	player_move_back(t_info *info)
{
	double	mvx;
	double	mvy;

	mvx = -1 * info->pos->dir_x * info->pos->move_speed;
	mvy = -1 * info->pos->dir_y * info->pos->move_speed;
	if (info->map->world_map[(int)info->pos->pos_y][(int)(info->pos->pos_x + mvx)] == '0')
	{
		info->pos->pos_x += mvx;
	}
	if (info->map->world_map[(int)(info->pos->pos_y + mvy)][(int)info->pos->pos_x] == '0')
	{
		info->pos->pos_y += mvy;
	}
	return (1);
}

int	player_move_left(t_info *info)
{
	double	mvx;
	double	mvy;

	mvx = info->pos->plane_x * info->pos->move_speed;
	mvy = info->pos->plane_y * info->pos->move_speed;
	if (info->map->world_map[(int)info->pos->pos_y][(int)(info->pos->pos_x + mvx)] == '0')
	{
		info->pos->pos_x += mvx;
	}
	if (info->map->world_map[(int)(info->pos->pos_y + mvy)][(int)info->pos->pos_x] == '0')
	{
		info->pos->pos_y += mvy;
	}
	return (1);
}

int	player_move_right(t_info *info)
{
	double	mvx;
	double	mvy;

	mvx = info->pos->plane_x * info->pos->move_speed * -1;
	mvy = info->pos->plane_y * info->pos->move_speed * -1;
	if (info->map->world_map[(int)info->pos->pos_y][(int)(info->pos->pos_x + mvx)] == '0')
	{
		info->pos->pos_x += mvx;
	}
	if (info->map->world_map[(int)(info->pos->pos_y + mvy)][(int)info->pos->pos_x] == '0')
	{
		info->pos->pos_y += mvy;
	}
	return (1);
}

int	rotate_left(t_info *info)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = info->pos->dir_x;
	info->pos->dir_x = info->pos->dir_x * cos(info->pos->rot_speed) - info->pos->dir_y * sin(info->pos->rot_speed);
	info->pos->dir_y = old_dir_x * sin(info->pos->rot_speed) + info->pos->dir_y * cos(info->pos->rot_speed);
	old_plane_x = info->pos->plane_x;
	info->pos->plane_x = info->pos->plane_x * cos(info->pos->rot_speed) - info->pos->plane_y * sin(info->pos->rot_speed);
	info->pos->plane_y = old_plane_x * sin(info->pos->rot_speed) + info->pos->plane_y * cos(info->pos->rot_speed);
	return (1);
}

int	rotate_right(t_info *info)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = info->pos->dir_x;
	info->pos->dir_x = info->pos->dir_x * cos(-info->pos->rot_speed) - info->pos->dir_y * sin(-info->pos->rot_speed);
	info->pos->dir_y = old_dir_x * sin(-info->pos->rot_speed) + info->pos->dir_y * cos(-info->pos->rot_speed);
	old_plane_x = info->pos->plane_x;
	info->pos->plane_x = info->pos->plane_x * cos(-info->pos->rot_speed) - info->pos->plane_y * sin(-info->pos->rot_speed);
	info->pos->plane_y = old_plane_x * sin(-info->pos->rot_speed) + info->pos->plane_y * cos(-info->pos->rot_speed);
	return (1);
}

//정상작동:1 오류:0
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
		return (rotate_left(info));
	if (info->key->right == 1)
		return (rotate_right(info));
	// if (info->key->e == 1)
	// 	return (rotate_mouse(info));
	return (0);
}
