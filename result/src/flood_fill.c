/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:14:25 by yeju              #+#    #+#             */
/*   Updated: 2022/05/18 20:41:01 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	check_fill(t_info *info)
{
	int	y;
	int	x;

	y = -1;
	while (++y < info->map->map_height)
	{
		x = -1;
		while (++x < info->map->map_width)
		{
			if (!utils_white_space(info->map->world_map[y][x]))
			{
				if ((info->map->world_map[y][x] != '1' && info->map->world_map[y][x] != '2'))
				{
					return (0);
				}
			}
		}
	}
	return (1);
}


int	is_save(int x, int y, t_info *info)
{
	return(0 <= x && x < info->map->map_width + 1 && 0 <= y && y < info->map->map_height + 1);
}

int	flood_fill(int pox, int poy, t_info *info)
{
				//동 서 남 북
	int dx[4] = {1, 0, -1, 0};
	int dy[4] = {0, 1, 0, -1};
	int idx;
	int nx;
	int ny;
	
	idx = 0;
	info->map->world_map[poy][pox] = '2';
	for (int i = 0; i < info->map->map_height+1; i++)
		printf("%s\n", info->map->world_map[i]);
	printf("\n");
	while (idx < 4)
	{
		nx = pox + dx[idx];
		ny = poy + dy[idx];
		if (is_save(nx, ny, info) && info->map->world_map[ny][nx] == '0')
		{
			printf("nx, ny: %d, %d\n", nx, ny);
			// info->map->world_map[ny][nx] = '2';
			flood_fill(nx, ny, info);
		}
		else if (is_save(nx, ny, info) && (info->map->world_map[ny][nx] != '0' || info->map->world_map[ny][nx] != '1' || info->map->world_map[ny][nx] != '2'))
		{
			return (0);
		}
		idx++;
	}
	return (check_fill(info));
}