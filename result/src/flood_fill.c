/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:30:12 by yeju              #+#    #+#             */
/*   Updated: 2022/05/22 13:18:30 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	check_fill_2(t_info *info)
{
	while (utils_white_space(info->map->world_map[info->word->cur_y][info->word->cur_x]))
		info->word->cur_x++;
	if (info->map->world_map[info->word->cur_y][info->word->cur_x] == '\0')
	{
		if (info->word->cur_y != info->map->map_height)
		{
			info->word->cur_y++;
			info->word->cur_x = 0;
		}
		else
		{
			return (1);
		}
	}
	// printf("y, x: %d, %d\n", info->word->cur_y, info->word->cur_x);
	if (utils_white_space(info->map->world_map[info->word->cur_y][info->word->cur_x]) || \
		info->map->world_map[info->word->cur_y][info->word->cur_x] == '1' || \
		info->map->world_map[info->word->cur_y][info->word->cur_x] == '2')
	{
		return (1);
	}
	// for (int i = 0; i < info->map->map_height + 1; i++)
	// {
	// 	for (int j = 0; j < info->map->map_width; j++)
	// 	{
	// 		printf("%c", info->map->world_map[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");
	// printf("res: %c", info->map->world_map[info->word->cur_y][info->word->cur_x]);
	return (0);
}

int	check_fill(t_info *info)
{
	info->word->cur_y = 0;
	while (info->word->cur_y < info->map->map_height)
	{
		info->word->cur_x = 0;
		while (info->word->cur_x < info->map->map_width)
		{
			if (!check_fill_2(info))
			{
				return (0);
			}
			info->word->cur_x++;
		}
		info->word->cur_y++;
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
		while (is_save(nx, ny, info) && (info->map->world_map[ny][nx] == '0'))
		{
			flood_fill(nx, ny, info);
		}
		idx++;
	}
	return (check_fill(info));
}
