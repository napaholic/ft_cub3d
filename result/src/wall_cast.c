#include "../inc/Cub3D.h"

void	set_wall_data(t_wall_data *wall_data, t_info *info)
{
	wall_data->lineheight = (int)(info->win_hei / wall_data->perp_wall_dist);
	wall_data->draw_start = -wall_data->lineheight / 2 + info->win_hei / 2;
	if (wall_data->draw_start < 0)
		wall_data->draw_start = 0;
	wall_data->draw_end = wall_data->lineheight / 2 + info->win_hei / 2;
	if (wall_data->draw_end >= info->win_hei)
		wall_data->draw_end = info->win_hei - 1;
	if (wall_data->side == 0)
		wall_data->wallx = info->pos->pos_y + wall_data->perp_wall_dist * wall_data->raydir_y;
	else
		wall_data->wallx = info->pos->pos_x + wall_data->perp_wall_dist * wall_data->raydir_x;
	wall_data->wallx -= floor((wall_data->wallx));
}

void	set_texture_data(t_wall_data *wall_data, t_info *info)
{
	wall_data->tex_x = (int)(wall_data->wallx * (double)TEX_WIDTH);
	if (wall_data->side == 0 && wall_data->raydir_x > 0)
		wall_data->tex_x = TEX_WIDTH - wall_data->tex_x - 1;
	if (wall_data->side == 1 && wall_data->raydir_x < 0)
		wall_data->tex_x = TEX_WIDTH - wall_data->tex_x - 1;
	wall_data->step_val = 1.0 * TEX_WIDTH / wall_data->lineheight;
	wall_data->tex_pos = (wall_data->draw_start - info->win_hei / 2 + wall_data->lineheight / 2) * wall_data->step_val;
}

int		set_color(t_wall_data *wall_data, t_info *info)
{
	int texY;
	int color=0; //=0
	int texnum;

	texY = (int)wall_data->tex_pos & (TEX_HEIGHT - 1);
	wall_data->tex_pos += wall_data->step_val;
	texnum = 0;
	if (wall_data->side && wall_data->step_y == POSITIVE)
		texnum = TEX_WALL_N;
	else if (wall_data->side && wall_data->step_y == NEGATIVE)
		texnum = TEX_WALL_S;
	else if (!wall_data->side && wall_data->step_x == POSITIVE)
		texnum = TEX_WALL_E;
	else if (!wall_data->side && wall_data->step_x == NEGATIVE)
		texnum = TEX_WALL_W;
	(void)info;
	color = info->texture[texnum][TEX_HEIGHT * texY + wall_data->tex_x];
	if (wall_data->side == 1)
		color = (color >> 1) & 8355711;
	return (color);
}