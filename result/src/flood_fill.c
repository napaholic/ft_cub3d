/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:30:12 by yeju              #+#    #+#             */
/*   Updated: 2022/05/20 09:55:52 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	check_fill(t_info *info)
{
	int	y;
	int	x;

	//test code
	// for (int i = 0; i < info->map->map_height+1; i++)
	// 	printf("%s\n", info->map->world_map[i]);
	// printf("\n");
	y = 0;
	while (y < info->map->map_height)
	{
		x = 0;
		while (x < info->map->map_width)
		{
			// printf("utils: %d\n", utils_white_space(info->map->world_map[y][x]));
			// printf("1: %d\n", info->map->world_map[y][x] != '1');
			// printf("2: %d\n", info->map->world_map[y][x] != '2');
			printf("x: %d, y: %d\n", x, y);
			if (!utils_white_space(info->map->world_map[y][x]) && !(info->map->world_map[y][x] == '1' || info->map->world_map[y][x] == '2'))
			{
				if (info->map->world_map[y][x] == '\n')
				{
					y++;
					printf("test %d", info->map->world_map[y][x]);
					// return (0);
				}
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_player_in_wall(int nx, int ny, t_info *info)
{
	if (nx < 0 || nx > info->map->map_width || ny < 0 || ny > info->map->map_height)
		return (0);
	return (1);
}

int	is_save(int x, int y, t_info *info)
{
	return(0 <= x && x < info->map->map_width + 1 && 0 <= y && y < info->map->map_height + 1);
}

int	flood_fill(int pox, int poy, t_info *info)
{
	int dx[8] = {1, 0, -1, 0, 1, -1, 1, -1};
	int dy[8] = {0, 1, 0, -1, 1, -1, -1, 1};
	int idx;
	int nx;
	int ny;
	
	idx = 0;
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