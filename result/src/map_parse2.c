/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:18:47 by yeju              #+#    #+#             */
/*   Updated: 2022/05/20 11:38:57 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	read_txt_path(char *line, int first, int second, int idx, t_info *info)
{
	char	*path;

	if (!utils_check_txt_path(line))
	{
		printf("Error\n wrong path: %s\n", line);
		exit(1);
	}
	path = get_texture_path(line, idx);
	if (!path)
		return (0);
	if (!utils_check_txt_execute(path))
	{
		printf("Error\n wrong path: %s\n", line);
		exit(1);
	}
	while (utils_white_space(line[idx]))
		++idx;
	if (first == 'N' && second == 'O')
		info->path->path_n = path;
	if (first == 'S' && second == 'O')
		info->path->path_s = path;
	if (first == 'E' && second == 'A')
		info->path->path_e = path;
	if (first == 'W' && second == 'E')
		info->path->path_w = path;
	return (1);
}

int	utils_check_color(char *line, int c, int idx)
{
	int	i;

	i = 0;
	while (utils_white_space(line[idx]))
		idx++;
	if (line[idx] == c)
		i = idx + 1;
	while (utils_white_space(line[i]))
		i++;
	while (utils_isdigit(line[i]) || line[i] == ',' || line[i] == '+')
		i++;
	while (utils_white_space(line[i]))
		i++;
	if (line[i] != '\0')
		return (0);
	return (1);
}

int	get_rgb_value(char *line)
{
	int		rgb;
	char	**split_rgb;
	int		r;
	int		g;
	int		b;

	rgb = 0;
	line++;
	while (utils_white_space(*line))
		line++;
	split_rgb = utils_split(line, ',');
	if (!split_rgb[0] || !split_rgb[1] || !split_rgb[2])
	{
		printf("Error\n empty color\n");
		exit(1);
	}
	r = utils_atoi(split_rgb[0]);
	g = utils_atoi(split_rgb[1]);
	b = utils_atoi(split_rgb[2]);
	if (0 <= r && r <= 255 && 0 <= g && g <= 255 && 0 <= b && b <= 255)
	{
		rgb = r;
		rgb = (rgb << 8) + g;
		rgb = (rgb << 8) + b;
		utils_free_split(split_rgb);
		return (rgb);
	}
	else
	{
		printf("Error\n wrong color\n");
		exit(1);
	}
}

int	read_color(char *line, int c, int idx, t_info *info)
{
	int	rgb;

	rgb = 0;
	if (!utils_check_color(line, c, idx))
	{
		printf("Error\n wrong color\n");
		exit(1);
	}
	rgb = get_rgb_value(line);
	if (!rgb)
	{
		printf("Error\n incorrect color\n");
		exit(1);
	}
	if (c == 'F')
		info->floor_color = rgb;
	if (c == 'C')
		info->ceiling_color = rgb;
	free(line);
	return (1);
}

int	read_map_setting(char *line, int idx, t_info *info)
{
	int	first;
	int	second;

	if (line[idx] && line[idx + 1])
	{
		first = line[idx];
		second = line[idx + 1];
	}
	else
		return (2);
	if (first == 'N' || first == 'W' || first == 'E' || first == 'S')
	{
		if (read_txt_path(line, first, second, idx, info) == 0)
		{
			printf("invalid map file format");
			exit(1);
		}
		if (first == 'F' || first == 'C')
			read_color(line, line[idx], idx, info);
	}
	return (1);
}
