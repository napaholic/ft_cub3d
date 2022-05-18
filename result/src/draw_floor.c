#include "../inc/Cub3D.h"

void	draw(t_info *info)
{
	int y;
	int x;

	y = -1;
	while (++y < info->win_hei)
	{
		x = -1;
		while (++x < info->win_wid)
			info->img->data[y * info->win_wid + x] = info->buf[x][y];
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img->img, 0, 0);
}
