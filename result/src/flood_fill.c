/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:14:25 by yeju              #+#    #+#             */
/*   Updated: 2022/05/18 18:52:59 by yeju             ###   ########.fr       */
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

// void	utils_check_fill()

int	flood_fill(int pox, int poy, t_info *info)
{
	info->map->world_map[poy][pox] = '2';
	if (pox + 1 >= 0 && pox + 1 <= info->map->map_width - 1 && info->map->world_map[poy][pox + 1] != '2' && info->map->world_map[poy][pox + 1] != '1')
	{
		flood_fill(pox + 1, poy, info);
	}
	if (pox - 1 >= 0 && pox - 1 <= info->map->map_width - 1 && info->map->world_map[poy][pox - 1] != '2' && info->map->world_map[poy][pox - 1] != '1')
	{
		flood_fill(pox - 1, poy, info);
	}
	if (poy + 1 >= 0 && poy + 1 <= info->map->map_height - 1 && info->map->world_map[poy + 1][pox] != '2' && info->map->world_map[poy + 1][pox] != '1')
	{
		flood_fill(pox, poy + 1, info);
	}
	if (poy - 1 >= 0 && poy - 1 <= info->map->map_height - 1 && info->map->world_map[poy - 1][pox] != '2' && info->map->world_map[poy - 1][pox] != '1')
	{
		flood_fill(pox, poy - 1, info);
	}
	return (check_fill(info));
}