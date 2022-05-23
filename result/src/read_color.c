/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:14:58 by yeju              #+#    #+#             */
/*   Updated: 2022/05/23 11:37:47 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

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
	while (utils_white_space(line[i]) || utils_isdigit(line[i]) \
		|| line[i] == ',' || line[i] == '+')
		i++;
	while (utils_white_space(line[i]))
		i++;
	if (line[i] != '\0')
		return (0);
	return (1);
}

int	get_only_num(char *color)
{
	int	idx;
	int	ret;

	idx = 0;
	while (utils_white_space(color[idx]) || color[idx] == '+')
		idx++;
	ret = utils_atoi(&color[idx]);
	return (ret);
}

int	get_rgb_value(char *line)
{
	char	**split_rgb;
	int		arr[4];

	line++;
	while (utils_white_space(*line))
		line++;
	split_rgb = utils_split(line, ',');
	if (!split_rgb[0] || !split_rgb[1] || !split_rgb[2])
		print_exit("empty color");
	arr[0] = get_only_num(split_rgb[0]);
	arr[1] = get_only_num(split_rgb[1]);
	arr[2] = get_only_num(split_rgb[2]);
	if (0 <= arr[0] && arr[0] <= 255 && 0 <= arr[1] && arr[1] <= 255 \
		&& 0 <= arr[2] && arr[2] <= 255)
	{
		arr[3] = arr[0];
		arr[3] = (arr[3] << 8) + arr[1];
		arr[3] = (arr[3] << 8) + arr[2];
		utils_free_split(split_rgb);
		return (arr[3]);
	}
	else
		print_exit("wrong color");
	return (0);
}

int	read_color(char *line, int c, int idx, t_info *info)
{
	int	rgb;

	rgb = 0;
	if (!utils_check_color(line, c, idx))
		print_exit("wrong color");
	rgb = get_rgb_value(line);
	if (!rgb)
		print_exit("incorrect color");
	if (c == 'F')
		info->floor_color = rgb;
	if (c == 'C')
		info->ceiling_color = rgb;
	if (line)
		free(line);
	return (1);
}
