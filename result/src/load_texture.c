/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:17:45 by yeju              #+#    #+#             */
/*   Updated: 2022/05/23 09:14:13 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, \
		&img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel, \
		&img->size_line, &img->endian);
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
			x += 1;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	img;

	init_texture(info);
	load_image(info, info->texture[0], info->path->path_n, &img);
	load_image(info, info->texture[1], info->path->path_s, &img);
	load_image(info, info->texture[2], info->path->path_e, &img);
	load_image(info, info->texture[3], info->path->path_w, &img);
}

void	init_texture(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	info->texture = (int **)malloc(sizeof(int *) * 4);
	while (i < 4)
	{
		info->texture[i] = (int *)malloc(sizeof(int) * \
			(info->win_hei * info->win_wid));
		i++;
	}
	i = 0;
	j = 0;
	while (i < 4)
	{
		while (j < info->win_hei * info->win_wid)
		{
			info->texture[i][j] = 0;
			j++;
		}
		i++;
	}
}
