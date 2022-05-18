/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:16:26 by yeju              #+#    #+#             */
/*   Updated: 2022/05/18 20:18:16 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	utils_check_txt_path(char *line)
{
	int	i;

	i = 0;
	while (utils_white_space(line[i]))
		++i;
	if ((line[i] != 'N' && line[i] != 'S' && line[i] != 'W' && line[i] != 'E') || \
		(line[i + 1] != 'O' && line[i + 1] != 'E' && line[i + 1] != 'A'))
		return (0);
	i += 2;
	while (utils_white_space(line[i]))
		++i;
	if (line[i] != '.' && line[i + 1] != '/')
		return (0);
	while (utils_isprint(line[i]) && !utils_white_space(line[i]) && line[i] != '\0')
		i++;
	while (utils_white_space(line[i]))
		i++;
	if (line[i] != '\0')
		return (0);
	return (1);
}

//txt path가 유효한지 확인
int	utils_check_txt_execute(char *path)
{
	// int	fd;
	int	len;

	len = utils_strlen(path);
	// fd = open(path, O_RDONLY); //이 부분은 texture_set의 mlx_xpm_file_to_image에서 체크해준다.
	// if (fd == -1)
	// {
	// 	close(fd);
	// 	return (0);
	// }
	if (path[len - 1] != 'm' || path[len - 2] != 'p' || \
		path[len - 3] != 'x' || path[len - 4] != '.')
		return (0);
	return (1);
}

char	*utils_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	new_len;

	if (s == NULL)
		return (NULL);
	if (utils_strlen(s) < start)
		return (utils_strdup(""));
	new_len = utils_strlen(s + start);
	if (new_len < len)
		len = new_len;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	utils_strlcpy(substr, s + start, len + 1);
	return (substr);
}

int	utils_get_size(char *str, int idx)
{
	int	ret;

	ret = 0;
	while (utils_isprint(str[idx + ret]) && !utils_white_space(str[idx + ret]))
		++ret;
	return (ret);
}

char *get_texture_path(char *line, int idx)
{
	char	*path;
	
	idx += 3;
	path = utils_substr(line, idx, utils_get_size(line, idx));
	return (path);
}

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
	utils_check_txt_execute(path);
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
	while (utils_isdigit(line[i]) || line[i] == ',')
		i++;
	while (utils_white_space(line[i]))
		i++;
	if (line[i] != '\0')
		return (0);
	return (1);
}

int	get_rgb_value(char *line)
{
	int	rgb;
	char **split_rgb;
	int	r;
	int	g;
	int	b;

	rgb = 0;
	line++;
	while (utils_white_space(*line))
		line++;
	split_rgb = utils_split(line, ',');
	r = utils_atoi(split_rgb[0]);
	g = utils_atoi(split_rgb[1]);
	b = utils_atoi(split_rgb[2]);

	rgb = r;
	rgb = (rgb << 8) + g;
	rgb = (rgb << 8) + b;
	utils_free_split(split_rgb);
	return (rgb);
}

int	read_color(char *line, int c, int idx, t_info *info)
{
	int	rgb;

	rgb = 0;
	//잘못된 형식인지 확인 //@
	if (!utils_check_color(line, c, idx))
	{
		printf("Error\n wrong color\n");
		exit(1);
	}
	rgb = get_rgb_value(line);
	if (c == 'F')
		info->floor_color = rgb;
	else if (c == 'C')
		info->ceiling_color = rgb;
	free(line);
	return (1);
}

int	read_map_setting(char *line, int idx, t_info *info)
{
	int	ret;
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
		ret = read_txt_path(line, first, second, idx, info);
	// else if (first == 'F' || first == 'C')
	// 	ret = read_color(line, line[idx], idx, info);
	return (1);
}

int	map_check(char *line, char **map, int idx, int gnl_ret)
{
	if (utils_white_space(line[idx]) || line[idx] == '1' || line[idx] == '0')
	{
		*map = utils_strjoin(*map, line);
		if (*map[i] == '\n' && *map[i + 1] == '\n') //@
			return (0);
		if (gnl_ret != 0 && line[idx])
			*map = utils_strjoin(*map, "\n");
		// free(line);
		return (1);
	}
	return (0);
}

int	read_map_sub(char *line, char **map, t_info *info, int gnl_ret)
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
		map_check(line, map, idx, gnl_ret);
	}
	return (1);
}

char	*read_map(char *argv, t_info *info)
{
	int		fd;
	int		ret;
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
	while ((ret = get_next_line(fd, &line)) != -1)
	{
		if (line && !read_map_sub(line, &map, info, ret))
			return (0);
		line = NULL;
		if (ret == 0)
			break ;
	}
	free(line);
	return (map);
}