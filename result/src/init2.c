/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:17:22 by yeju              #+#    #+#             */
/*   Updated: 2022/05/23 09:30:29 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	init_path(t_info *info)
{
	info->path = (t_path *)malloc(sizeof(t_path));
	if (!info->path)
		return (0);
	utils_bzero(info->path, sizeof(t_path));
	return (1);
}

int	init_word(t_info *info)
{
	info->word = (t_word *)malloc(sizeof(t_word));
	if (!info->word)
		return (0);
	utils_bzero(info->word, sizeof(t_word));
	return (1);
}

int	init_info(t_info *info, char *argv)
{
	if (!init_map(info, argv) || !init_path(info) || !init_word(info) \
	|| !init_key(info) || !init_player(info) || !init_win_img(info))
		return (0);
	return (1);
}

t_info	*init_info_mlx(void)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		print_exit("info malloc error");
	utils_bzero(info, sizeof(t_info));
	info->mlx = mlx_init();
	if (!info->mlx)
		return (0);
	info->win_wid = 640;
	info->win_hei = 480;
	return (info);
}
