#include "../inc/Cub3D.h"

void	set_raydir(t_floordata *floor, t_info *info, int y)
{
	floor->ray_dir_x0 = info->pos->dir_x - info->pos->plane_x;
	floor->ray_dir_y0 = info->pos->dir_y - info->pos->plane_y;
	floor->ray_dir_x1 = info->pos->dir_x + info->pos->plane_x;
	floor->ray_dir_y1 = info->pos->dir_y + info->pos->plane_y;
	floor->row_distance = (0.5 * info->win_hei) / (y - info->win_hei / 2);
}

void	set_floor_vec(t_floordata *floor, t_info *info)
{
	floor->floor_stepX = floor->row_distance
			*(floor->ray_dir_x1 - floor->ray_dir_x0) / info->win_wid;
	floor->floor_stepY = floor->row_distance
			* (floor->ray_dir_y1 - floor->ray_dir_y0) / info->win_wid;
	floor->floorX = info->pos->pos_x + floor->row_distance * floor->ray_dir_x0;
	floor->floorY = info->pos->pos_y + floor->row_distance * floor->ray_dir_y0;
}

void	set_texture_vec(t_floordata *floor, t_info *info)
{
	floor->cellX = (int)(floor->floorX);
	floor->cellY = (int)(floor->floorY);
	floor->dX = (int)(info->txt[TEX_FLOOR_1]->img_width * (floor->floorX - floor->cellX)) & (info->txt[TEX_FLOOR_1]->img_width - 1);
	floor->dY = (int)(info->txt[TEX_CEILING]->img_width * (floor->floorY - floor->cellY)) & (info->txt[TEX_CEILING]->img_height - 1);
	floor->floorX += floor->floor_stepX;
	floor->floorY += floor->floor_stepY;
}

void	set_texture_num(t_floordata *floor)
{
	int	tile_define = ((int)floor->floorX + (int)floor->floorY) % 2;

	floor->ceiling_texture = TEX_CEILING;
	if (tile_define)
		floor->floorTexture = TEX_FLOOR_1;
	else
		floor->floorTexture = TEX_FLOOR_2;
}

void	floor_cast(t_info *info) {
	t_floordata f_data;
	int	x;
	int	y;

	y = info->win_hei / 2 - 1;
	while (++y < info->win_hei) {

		set_raydir(&f_data, info, y);
		set_floor_vec(&f_data, info);
		x = -1;
		while (++x < info->win_wid)
		{
			set_texture_vec(&f_data, info);
			set_texture_num(&f_data);
			render_floor(&f_data, info, x, y);
			//모르겠음
		}
	}
}



