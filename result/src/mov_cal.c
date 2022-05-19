#include "../inc/Cub3D.h"

int	empty_chk_map(t_map *map, int x, int y)
{
	if (map->world_map[x][y] == 0)
		return (0);
	return (1);
}

int	rotate_mouse(t_info *info)
{
	int	x;
	int	y;

	if (info->key->e == 1)
	{
		mlx_mouse_hide();
		if (info->key->e_delay++ < 5)
			mlx_mouse_move(info->win, info->win_wid / 2, info->win_hei / 2);
		else
		{
			mlx_mouse_get_pos(info->win, &x, &y);
			//vec_mrot(info, -(2.0 * x / info-> - 1) * 160);
			printf("x = %d, y = %d", x, y);
			mlx_mouse_move(info->win, info->win_wid / 2, info->win_hei / 2);
		}
	}
	else
	{
		mlx_mouse_show();
		info->key->e_delay = 0;
	}
	return (1);
}
