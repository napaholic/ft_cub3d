/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:07:07 by yeju              #+#    #+#             */
/*   Updated: 2022/05/20 21:33:09 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void	save_map_get_size_2(char *line_map, t_info *info, int hei, int i)
{
	int		wid;
	int		wid2;

	i = 0;
	wid = 0;
	wid2 = 0;
	info->map->map_height = hei;
	while (hei--)
	{
		info->map->map_width = wid2;
		wid = 0;
		while (line_map[i++] != '\n')
			wid++;
		if (wid2 < wid)
			wid2 = wid;
	}
	return ;
}

void	save_map_get_size(char *line_map, t_info *info)
{
	size_t	i;
	int		hei;

	i = 0;
	hei = 0;
	while (line_map[i] != '\0')
	{
		if (line_map[i] == '\n')
		{
			if (i != utils_strlen(line_map) - 1)
			{
				++hei;
			}
		}
		i++;
	}
	save_map_get_size_2(line_map, info, hei, i);
	return ;
}

void	save_map_2(char *line_map, t_info *info)
{
	int	idx;

	idx = 0;
	if (info->map->world_map)
		free(info->map->world_map);
	save_map_get_size(line_map, info);
	info->map->world_map = (char **)malloc(sizeof(char *) * \
		info->map->map_height);
	utils_bzero(info->map->world_map, sizeof(char *) * info->map->map_height);
	while (idx++ < info->map->map_height)
	{
		info->map->world_map[idx] = (char *)malloc(sizeof(char) * \
			info->map->map_width);
		utils_bzero(info->map->world_map[idx], sizeof(char) * \
			info->map->map_width);
	}
}

char	**save_map(char *line_map, t_info *info)
{
	save_map_2(line_map, info);
	info->map->world_map = utils_split(line_map, '\n');
	if (!*info->map->world_map)
		print_exit("Error\n empty map");
	set_pos(info->map->world_map, info);
	if (info->pos->pos_x == -20.0 || info->pos->pos_y == -20.0)
		print_exit("Error\n pos setting");
	if (!flood_fill((int)info->pos->pos_x, (int)info->pos->pos_y, info))
		print_exit("Error\n incorrect map");
	free(line_map);
	return (info->map->world_map);
}
