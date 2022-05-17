/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:16:26 by yeju              #+#    #+#             */
/*   Updated: 2022/05/13 09:10:23 by yeju             ###   ########.fr       */
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

//실패시 0반환 (파일권한도동일)
//int	texture_set(t_info *info, char *path, int idx)
//{
//	if (!utils_check_txt_execute(path))
//		return (0);
//	//test code
//	// printf("txt path is: %s\n", path);
//	info->txt[idx]->img = mlx_xpm_file_to_image(info->mlx, path, \
//		&info->txt[idx]->img_width, &info->txt[idx]->img_height);
//	if (!info->txt[idx])
//		return (0);
//	info->txt[idx]->data = (int *)mlx_get_data_addr(info->txt[idx]->img, \
//		&info->txt[idx]->bits_per_pixel, &info->txt[idx]->size_line, &info->txt[idx]->endian);
//	//test code
//	// printf("imgheght: %d\n", info->txt[idx]->img_height);
//	free(path);
//	return (1);
//}

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
	
	idx += 3; //'NO '건너띈부분
	path = utils_substr(line, idx, utils_get_size(line, idx));
	return (path);
}

//int	read_txt_path(char *line, int first, int second, int idx, t_info *info)
//{
//	char	*path;
//
//	if (!utils_check_txt_path(line))
//	{
//		printf("Error\n wrong path: %s\n", line);
//		exit(1);
//	}
//	path = get_texture_path(line, idx); //path만 따로 저장하는 함수
//	if (!path)
//		return (0);
//	utils_check_txt_execute(path); //path가 유효한지 확인
//	while (utils_white_space(line[idx]))
//		++idx;
//	if (first == 'N' && second == 'O')
//		return (texture_set(info, path, TEX_WALL_N));
//	if (first == 'S' && second == 'O')
//		return (texture_set(info, path, TEX_WALL_S));
//	if (first == 'E' && second == 'A')
//		return (texture_set(info, path, TEX_WALL_E));
//	if (first == 'W' && second == 'E')
//		return (texture_set(info, path, TEX_WALL_W));
//	else
//		return (0);
//}

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
	// test code
	// printf("rgb: %d\n", rgb);
	utils_free_split(split_rgb);
	return (rgb);
}

//@
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
	rgb = get_rgb_value(line); //rgb로 변환해서 rgb에 담기
	// 저장해주기
	if (c == 'F')
		info->floor_color = rgb;
	else if (c == 'C')
		info->ceiling_color = rgb;
	free(line); //free확인하기
	return (1);
}

//반환값: 2:종료,오류 / 1: 정상작동
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
	info->win_hei = info->win_hei;//<- test code
//	if (first == 'N' || first == 'W' || first == 'E' || first == 'S')
//		ret = read_txt_path(line, first, second, idx, info);
//	else if (first == 'F' || first == 'C')
//		ret = read_color(line, line[idx], idx, info);
//	else
//		ret = 2;
	ret = 1;
	return (ret);
}

int	map_check(char *line, char **map, int idx, int gnl_ret)
{
	if (utils_white_space(line[idx]) || line[idx] == '1' || line[idx] == '0')
	{
		*map = utils_strjoin(*map, line);
		if (gnl_ret != 0 && line[idx])
			*map = utils_strjoin(*map, "\n");
		// free(line);//line free확인하기 //@
		return (1);
	}
	return (0);
}

int	read_map_sub(char *line, char **map, t_info *info, int gnl_ret)
{
	int	idx;
	int	ret;

	// (void)map;
	idx = 0;
	while (utils_white_space(line[idx]) == 1)
		++idx;
	//반환값: 2:종료,오류 / 1: 정상작동
	ret = read_map_setting(line, idx, info);  //map파일에 벽,바닥,천장 읽기
	if (ret == 0)
	{
		printf("%s\n", "end?");
		return (0);
	}
	else
	{
		map_check(line, map, idx, gnl_ret); //맵부분만 map(후에 line_map)에 저장
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
		//test
		// printf("1: %s\n", line);
		if (line && !read_map_sub(line, &map, info, ret))
			return (0);
		line = NULL;
		if (ret == 0)
			break ;
	}
	free(line);
	return (map);
}