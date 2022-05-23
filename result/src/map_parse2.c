/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:18:47 by yeju              #+#    #+#             */
/*   Updated: 2022/05/23 09:48:20 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	check_path(char **path, char *line, int idx)
{
	if (!utils_check_txt_path(line))
		print_exit("wrong path");
	*path = get_texture_path(line, idx);
	if (!*path)
		return (0);
	if (!utils_check_txt_execute(*path))
		print_exit("cannot open file");
	return (1);
}

int	read_txt_path(char *line, int idx, t_info *info)
{
	char	*path;

	path = NULL;
	if (!check_path(&path, line, idx))
		return (0);
	while (utils_white_space(line[idx]))
		++idx;
	if (info->word->first == 'N' && info->word->second == 'O')
		info->path->path_n = path;
	if (info->word->first == 'S' && info->word->second == 'O')
		info->path->path_s = path;
	if (info->word->first == 'E' && info->word->second == 'A')
		info->path->path_e = path;
	if (info->word->first == 'W' && info->word->second == 'E')
		info->path->path_w = path;
	return (1);
}

int	read_map_setting(char *line, int idx, t_info *info)
{
	if (line[idx] && line[idx + 1])
	{
		info->word->first = line[idx];
		info->word->second = line[idx + 1];
	}
	else
		return (2);
	if (info->word->first == 'N' || info->word->first == 'W' \
		|| info->word->first == 'E' || info->word->first == 'S')
	{
		if (!read_txt_path(line, idx, info))
			print_exit("invalid map file format");
	}
	if (info->word->first == 'F' || info->word->first == 'C')
		read_color(line, line[idx], idx, info);
	return (1);
}
