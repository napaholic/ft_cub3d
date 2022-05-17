#include "../inc/Cub3D.h"

void	init_DDA_cast(t_wall_data *wall_data, t_info *info)
{
	if (wall_data->raydir_x < 0)
	{
		wall_data->step_x = -1;
		wall_data->side_dist_x = (info->pos->pos_x - wall_data->map_pos_x) \
			* wall_data->d_dist_x;
	}
	else
	{
		wall_data->step_x = 1;
		wall_data->side_dist_x = (wall_data->map_pos_x + 1.0 - info->pos->pos_x) \
			* wall_data->d_dist_x;
	}
	if (wall_data->raydir_y < 0)
	{
		wall_data->step_y = -1;
		wall_data->side_dist_y = (info->pos->pos_y - wall_data->map_pos_y) \
			* wall_data->d_dist_y;
	}
	else
	{
		wall_data->step_y = 1;
		wall_data->side_dist_y = (wall_data->map_pos_y + 1.0 - info->pos->pos_y) \
				* wall_data->d_dist_y;
	}
}

void	set_dda(t_wall_data *wall_data, t_info *info, int count)
{
	wall_data->camera_x = 2 * count / (double)info->win_wid - 1;
	wall_data->raydir_x = info->pos->dir_x + info->pos->plane_x * wall_data->camera_x;
	wall_data->raydir_y = info->pos->dir_y + info->pos->plane_y * wall_data->camera_x;
	wall_data->map_pos_x = (int)info->pos->pos_x;
	wall_data->map_pos_y = (int)info->pos->pos_y;
	wall_data->d_dist_x = fabs(1 / wall_data->raydir_x);
	wall_data->d_dist_y = fabs(1 / wall_data->raydir_y);
}

void	calc_perp_dist(t_wall_data *wall_data, t_info *info)
{
	if (wall_data->side == 0)
		wall_data->perp_wall_dist = (wall_data->map_pos_x - info->pos->pos_x + (1 - wall_data->step_x) / 2) / wall_data->raydir_x;
	else
		wall_data->perp_wall_dist = (wall_data->map_pos_y - info->pos->pos_y + (1 - wall_data->step_y) / 2) / wall_data->raydir_y;

	return ;
}

void	step_progress_until_hit(t_wall_data *wall_data, t_info *info)//벽에 맞을때까지 sideDist 증가. sideDist 가 나중에 perpWallDist 에 사용됨.
{
	wall_data->hit = 0;
	while (wall_data->hit == 0)
	{
		if (wall_data->side_dist_x < wall_data->side_dist_y)
		{
			wall_data->side_dist_x += wall_data->d_dist_x;
			wall_data->map_pos_x += wall_data->step_x;
			wall_data->side = 0;
		}
		else
		{
			wall_data->side_dist_y += wall_data->d_dist_y;
			wall_data->map_pos_y += wall_data->step_y;
			wall_data->side = 1;
		}
		if (info->map->world_map[wall_data->map_pos_y]
		[wall_data->map_pos_x] == '1')
			wall_data->hit = 1;
	}
} //hit이 wall_data안에 있어서 그걸로 교체

// void	wall_cast(t_info *info)d
// {
// 	t_wall_data *wall_data;
// 	int x;
// 	int y;

// 	x = -1;
// 	while (++x < info->win_wid)
// 	{
// 		//1. set_DDA
// 		set_DDA(wall_data, info, x);
// 		//2. wall_DistCast
// 		set_wall_data(wall_data, info);
// 		//3. wall_set_texture_data
// 		set_texture_data(wall_data, info);
// 		y = wall_data.draw_start - 1;
// 		while(++y < wall_data.draw_end)
// 			info->buf[y][x] = set_color(wall_data, info);
// 	}
// }