/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 06:23:51 by yeju              #+#    #+#             */
/*   Updated: 2022/05/11 13:22:10 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	utils_strchr(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	gnl_split(char **string, char **line, int i)
{
	char	*tmp;
	int		len;

	(*string)[i] = '\0';
	*line = utils_strdup(*string);
	len = utils_strlen(*string + i + 1);
	if (len == 0)
	{
		free(*string);
		*string = 0;
		return (1);
	}
	tmp = utils_strdup(*string + i + 1);
	free(*string);
	*string = tmp;
	return (1);
}

int	gnl_return(char **string, char **line, int read_size)
{
	int	i;

	if (read_size < 0)
		return (-1);
	i = utils_strchr(*string);
	if (*string && i >= 0)
		return (gnl_split(string, line, i));
	else if (*string)
	{
		*line = *string;
		*string = 0;
		return (0);
	}
	*line = utils_strdup("");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*string[32];
	char		buffer[256 + 1];
	int			read_size;
	int			i;

	if ((fd < 0) || (32 < fd) || (!line) || (256 <= 0))
		return (-1);
	read_size = 1;
	while (read_size > 0)
	{
		read_size = read(fd, buffer, 256);
		if (read_size < 0)
			break ;
		buffer[read_size] = '\0';
		string[fd] = utils_strjoin(string[fd], buffer);
		i = utils_strchr(string[fd]);
		if (i >= 0)
			return (gnl_split(&string[fd], line, i));
	}
	return (gnl_return(&string[fd], line, read_size));
}