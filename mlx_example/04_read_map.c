#include "04_header.h"

/*-===========================================-*/

size_t	ft_strlen_gnl(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	len;

	src_len = 0;
	while (src[src_len] != '\0')
	{
		src_len++;
	}
	if (dstsize == 0)
	{
		return (src_len);
	}
	len = 0;
	while (src[len] != '\0' && len < (dstsize - 1))
	{
		dest[len] = src[len];
		len++;
	}
	dest[len] = 0;
	return (src_len);
}

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen_gnl(dest);
	src_len = ft_strlen_gnl(src);
	len = 0;
	while (src[len] != '\0' && dest_len + 1 + len < dstsize)
	{
		dest[dest_len + len] = src[len];
		len++;
	}
	dest[dest_len + len] = '\0';
	if (dstsize < dest_len)
		return (dstsize + src_len);
	return (dest_len + src_len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*string;
	int		s1_len;
	int		s2_len;

	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
	{
		if (s1)
			return (ft_strdup(s1));
		return (ft_strdup(s2));
	}
	s1_len = ft_strlen_gnl(s1);
	s2_len = ft_strlen_gnl(s2);
	string = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!string)
		return (NULL);
	ft_strlcpy(string, s1, s1_len + 1);
	free(s1);
	ft_strlcat(string + (s1_len), s2, s2_len + 1);
	return (string);
}

char	*ft_strdup(char *s1)
{
	char	*new_str;
	int		len;
	int		i;

	len = ft_strlen_gnl(s1);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (0);
	i = 0;
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

int	ft_strchr(char *string)
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
	*line = ft_strdup(*string);
	len = ft_strlen_gnl(*string + i + 1);
	if (len == 0)
	{
		free(*string);
		*string = 0;
		return (1);
	}
	tmp = ft_strdup(*string + i + 1);
	free(*string);
	*string = tmp;
	return (1);
}

int	return_this(char **string, char **line, int read_size)
{
	int	i;

	if (read_size < 0)
		return (-1);
	i = ft_strchr(*string);
	if (*string && i >= 0)
		return (gnl_split(string, line, i));
	else if (*string)
	{
		*line = *string;
		*string = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*string[OPEN_MAX];
	char		buffer[BUFFER_SIZE + 1];
	int			read_size;
	int			i;

	if ((fd < 0) || (OPEN_MAX < fd) || (!line) || (BUFFER_SIZE <= 0))
		return (-1);
	read_size = 1;
	while (read_size > 0)
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size < 0)
			break ;
		buffer[read_size] = '\0';
		string[fd] = ft_strjoin(string[fd], buffer);
		i = ft_strchr(string[fd]);
		if (i >= 0)
			return (gnl_split(&string[fd], line, i));
	}
	return (return_this(&string[fd], line, read_size));
}

/*-===========================================-*/

int **save_int(char **map)
{
	int **ret_map = (int **)malloc(sizeof(int *) * mapWidth + 1);

	for (int l = 0; l < mapWidth; l++)
	{
		ret_map[l] = (int *)malloc(sizeof(int) * mapHeight + 1);
	}

	for (int i = 0; i < mapWidth; i++)
		for (int j = 0; j < mapHeight; j++)
			ret_map[i][j] = map[i][j] - '0';
	return (ret_map);
}

int	**read_map(char *argv)
{
	int		fd;
	char	*tmp;
	int		i;
	char	**map;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		printf("%s", "ERROR\n");
	i = 0;
	while ((get_next_line(fd, &tmp)))
	{
		free(tmp);
		i++;
	}
	free(tmp);
	map = (char **)malloc(sizeof(char *) * (i + 2));
	close(fd);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		printf("%s", "ERROR\n");
	i = 0;
	while ((get_next_line(fd, &map[i])))
		i++;
	map[++i] = 0;
	return (save_int(map));
}