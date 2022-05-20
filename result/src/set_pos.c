/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:03:30 by yeju              #+#    #+#             */
/*   Updated: 2022/05/20 20:03:32 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void	set_pos_2(char **world_map, t_info *info, int hei, int wid)
{
	if (world_map[hei][wid] == 'N')
		get_direction(info, world_map, hei, wid);
	else if (world_map[hei][wid] == 'W')
		get_direction(info, world_map, hei, wid);
	else if (world_map[hei][wid] == 'E')
		get_direction(info, world_map, hei, wid);
	else if (world_map[hei][wid] == 'S')
		get_direction(info, world_map, hei, wid);
}

void	set_pos(char **world_map, t_info *info)
{
	int	wid;
	int	hei;
	int	flag;

	flag = 0;
	hei = 0;
	while (hei <= info->map->map_height)
	{
		wid = 0;
		while (wid <= info->map->map_width)
		{
			if (world_map[hei][wid] == 'N' || world_map[hei][wid] == 'W' || \
				world_map[hei][wid] == 'E' || world_map[hei][wid] == 'S')
			{
				flag += 1;
				info->pos->pos_x = (double)wid + 0.5;
				info->pos->pos_y = (double)hei + 0.5;
			}
			set_pos_2(world_map, info, hei, wid);
			wid++;
		}
		hei++;
	}
	if (flag != 1)
		print_exit("Error\n there is multi player\n");
}
