/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:12:58 by yeju              #+#    #+#             */
/*   Updated: 2022/05/12 13:28:18 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	utils_white_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

int	utils_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

int	utils_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	utils_bzero(void *s, size_t n)
{
	char	*dest;
	size_t	i;

	dest = s;
	i = 0;
	while (i++ < n)
		*dest++ = 0;
}

int	utils_read_another(char *line, int i)
{
	if (line[i])
	{
		if (line[i] != '\0' && line[i] != '\n')
		{
			free(line);
			printf("%s", "ERROR: unknown identifier\n");
		}
	}
	return (1);
}

static int	utils_count_words(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*utils_word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**utils_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	split = malloc((utils_count_words(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= utils_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == utils_strlen(s)) && index >= 0)
		{
			split[j++] = utils_word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

int	utils_atoi(const char *str)
{
	int	minus;
	int	i;
	int	num;

	i = 0;
	minus = 1;
	num = 0;
	while ((str[i] != '\0') && utils_white_space(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * minus);
}

void	utils_free_split(char **split_rgb)
{
	int i;
	
	i = 0;
	while (split_rgb[i++])
		free(split_rgb[i]);
	free(split_rgb);
}