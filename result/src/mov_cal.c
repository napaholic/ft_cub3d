#include "../inc/Cub3D.h"

void    player_move_right(t_info *info)
{
	double mvx;
	double mvy;

	mvx = -info->pos->dir_y * info->pos->move_speed;
	mvy = info->pos->dir_x * info->pos->move_speed;
	if (info->map->world_map[(int)info->pos->pos_y][(int)(info->pos->pos_x + mvx)] == '0')
	{
		info->pos->pos_x += mvx;
	}
	if (info->map->world_map[(int)(info->pos->pos_y + mvy)][(int)info->pos->pos_x] == '0')
	{
		info->pos->pos_y += mvy;
	}
}

void    player_move_left(t_info *info)
{
	double mvx;
	double mvy;

	mvx = info->pos->dir_y * info->pos->move_speed;
	mvy = -info->pos->dir_x * info->pos->move_speed;
	if (info->map->world_map[(int)info->pos->pos_y][(int)(info->pos->pos_x + mvx)] == '0')
	{
		info->pos->pos_x += mvx;
	}
	if (info->map->world_map[(int)(info->pos->pos_y + mvy)][(int)info->pos->pos_x] == '0')
	{
		info->pos->pos_y += mvy;
	}
}

int	empty_chk_map(t_map *map, int x, int y)
{
	if (map->world_map[x][y] == 0)
		return (0);
	return (1);
}

void    vec_mrot(t_info *info, rot_speed)
{

}

void    rotate_mouse(t_info *info)
{
	int x;
	int y;
	if (info->key->e == 1)
	{
		mlx_mouse_hide();
		if (info->key->e_delay++ < 5)
			mlx_mouse_move(info->win, info->win_wid / 2, info->win_hei / 2);
		else
		{
			mlx_mouse_get_pos(info->win, &x, &y);
			vec_mrot(info, -(2.0 * x / WIDTH - 1) * 160);
			mlx_mouse_move(info->win, info->win_wid / 2, info->win_hei / 2);
		}
	}
	else
	{
		mlx_mouse_show();
		info->key->e_delay = 0;
	}
}