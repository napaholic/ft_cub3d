/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:14:58 by yeju              #+#    #+#             */
/*   Updated: 2022/05/23 09:50:39 by yeju             ###   ########.fr       */
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
	int		idx[3];

	rgb = 0;
	line++;
	while (utils_white_space(*line))
		line++;
	split_rgb = utils_split(line, ',');
	if (!split_rgb[0] || !split_rgb[1] || !split_rgb[2])
		print_exit("empty color");
	idx[0] = utils_atoi(split_rgb[0]);
	idx[1] = utils_atoi(split_rgb[1]);
	idx[2] = utils_atoi(split_rgb[2]);
	if (0 <= idx[0] && idx[0] <= 255 && 0 <= idx[1] && idx[1] <= 255
		&& 0 <= idx[2] && idx[2] <= 255)
	{
		rgb = idx[0];
		rgb = (rgb << 8) + idx[1];
		rgb = (rgb << 8) + idx[2];
		utils_free_split(split_rgb);
		return (rgb);
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
	free(line);
	return (1);
}
