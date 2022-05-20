/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:20:24 by yeju              #+#    #+#             */
/*   Updated: 2022/05/20 20:56:40 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	map_check(char *line, char **map, int idx, t_info *info)
{
	if (line[idx] == '1')
		info->flag = 1;
	if (!utils_strlen(line) && info->flag)
	{
		printf("Error\n empty line in map");
		exit(1);
	}
	if (utils_white_space(line[idx]) || line[idx] == '1' || line[idx] == '0')
	{
		*map = utils_strjoin(*map, line);
		if (info->word->gnl_ret != 0 && line[idx])
			*map = utils_strjoin(*map, "\n");
		free(line);
		return (1);
	}
	return (0);
}

int	read_map_sub(char *line, char **map, t_info *info)
{
	int	idx;
	int	ret;

	idx = 0;
	while (utils_white_space(line[idx]) == 1)
		++idx;
	ret = read_map_setting(line, idx, info);
	if (ret == 0)
	{
		printf("%s\n", "end?");
		return (0);
	}
	else
	{
		map_check(line, map, idx, info);
	}
	return (1);
}

char	*read_map(char *argv, t_info *info)
{
	int		fd;
	char	*map;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		printf("%s", "ERROR\n cannot open file\n");
		exit(1);
		return (0);
	}
	map = (char *)malloc(sizeof(char) * 2);
	utils_bzero(map, sizeof(char));
	line = (char *)malloc(sizeof(char) * 1);
	utils_bzero(line, sizeof(char));
	while ((info->word->gnl_ret = get_next_line(fd, &line)) != -1)
	{
		if (line && !read_map_sub(line, &map, info))
			return (0);
		line = NULL;
		if (info->word->gnl_ret == 0)
			break ;
	}
	free(line);
	return (map);
}
