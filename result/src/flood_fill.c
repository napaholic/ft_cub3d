/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:30:12 by yeju              #+#    #+#             */
/*   Updated: 2022/05/20 21:00:21 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	check_fill_2(t_info *info, int x, int y)
{
	if (info->map->world_map[y][x] == '\0')
	{
		if (y == info->map->map_height - 1)
			return (0);
		else
			y++;
		x = 0;
	}
	while (utils_white_space(info->map->world_map[y][x]))
		x++;
	if (!(utils_white_space(info->map->world_map[y][x]) || \
		info->map->world_map[y][x] == '1' || \
		info->map->world_map[y][x] == '2'))
	{
		return (0);
	}
	return (1);
}

int	check_fill(t_info *info)
{
	int	y;
	int	x;

	y = 0;
	while (y < info->map->map_height)
	{
		x = 0;
		while (x < info->map->map_width)
		{
			if (!check_fill_2(info, x, y))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	check_player_in_wall(int nx, int ny, t_info *info)
{
	if (nx < 0 || nx > info->map->map_width - 1 || \
		ny < 0 || ny > info->map->map_height)
	{
		return (0);
	}
	return (1);
}

int	is_save(int x, int y, t_info *info)
{
	return (0 <= x && x < info->map->map_width + 1 && \
		0 <= y && y < info->map->map_height + 1);
}

int	flood_fill(int pox, int poy, t_info *info)
{
	int	dx[8];
	int	dy[8];
	int	idx;
	int	nx;
	int	ny;

	idx = 0;
	set_arr(&dx[0], &dy[0]);
	info->map->world_map[poy][pox] = '2';
	while (idx < 8)
	{
		nx = pox + dx[idx];
		ny = poy + dy[idx];
		if (!check_player_in_wall(nx, ny, info))
		{
			printf("Error\n incorrect position");
			exit(1);
		}
		while (is_save(nx, ny, info) && info->map->world_map[ny][nx] == '0')
		{
			flood_fill(nx, ny, info);
		}
		idx++;
	}
	return (check_fill(info));
}
