/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:14:58 by yeju              #+#    #+#             */
/*   Updated: 2022/05/20 20:15:04 by yeju             ###   ########.fr       */
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
