/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:19:45 by yeju              #+#    #+#             */
/*   Updated: 2022/05/17 15:50:42 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void	set_north(t_info *info, int hei, int wid)
{
	info->pos->dir_x = 0;
	info->pos->dir_y = -1;
	info->pos->plane_x = 0.66;
	info->pos->plane_y = 0.0;
	info->map->world_map[hei][wid] = '0';
	printf("\nnorth\n");
}

void	set_west(t_info *info, int hei, int wid)
{
	info->pos->dir_x = -1;
	info->pos->dir_y = 0;
	info->pos->plane_x = 0.0;
	info->pos->plane_y = -0.66;
	info->map->world_map[hei][wid] = '0';
	printf("\nwest\n");
}

void	set_east(t_info *info, int hei, int wid)
{
	info->pos->dir_x = 1;
	info->pos->dir_y = 0;
	info->pos->plane_x = 0.0;
	info->pos->plane_y = 0.66;
	info->map->world_map[hei][wid] = '0';
	printf("\neast\n");
}

void	set_south(t_info *info, int hei, int wid)
{
	info->pos->dir_x = 0;
	info->pos->dir_y = 1;
	info->pos->plane_x = -0.66;
	info->pos->plane_y = 0.0;
	info->map->world_map[hei][wid] = '0';
	//worldmap이후에설정하는지확인
	printf("\nsouth\n");
}

void	get_direction(t_info *info, char **world_map, int hei, int wid)
{
	if (world_map[hei][wid] == 'N')
		set_north(info, hei, wid);
	if (world_map[hei][wid] == 'W')
		set_west(info, hei, wid);
	if (world_map[hei][wid] == 'E')
		set_east(info, hei, wid);
	if (world_map[hei][wid] == 'S')
		set_south(info, hei, wid);
	return ;
}
