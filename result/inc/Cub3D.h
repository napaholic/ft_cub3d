/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:28:46 by yeju              #+#    #+#             */
/*   Updated: 2022/05/20 11:33:35 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* include headers */
#include "../mlx/mlx.h"
#include <math.h>
#include <fcntl.h>

/*일단추가한헤더...*/
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* mlx */
# define X_KEY_PRESS	2
# define X_KEY_RELEASE	3
# define X_CLICK_EXIT	17

/* key */
# define KEY_ESC		53
# define KEY_A			0
# define KEY_D			2
# define KEY_S			1
# define KEY_W			13
# define KEY_E			14
# define KEY_LEFT		123
# define KEY_RIGHT		124

/* texture */
# define TEX_WALL_N		0
# define TEX_WALL_S		1
# define TEX_WALL_E		2
# define TEX_WALL_W		3
# define TEX_WIDTH      32
# define TEX_HEIGHT     32

/* step_vector */
# define POSITIVE 1
# define NEGATIVE -1

/* image struct */
typedef struct	s_img
{
	void	*img;
	int 	*data;
	int		img_width;
	int		img_height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*path;
}				t_img;

/* map struct */
typedef struct	s_map
{
	char	**world_map;
	char	*line_map;
	char	*map_name;
	int		map_width;
	int		map_height;
}				t_map;

/* key struct */
typedef struct	s_key
{
	int	w;
	int	a;
	int	s;
	int	d;
	int e;//마우스 시점변환 토글
	int e_delay;//마우스 딜레이
	int	left;
	int	right;
}				t_key;

/* pos struct */
typedef struct	s_pos
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}				t_pos;

/* wall_data struct */
typedef struct	s_wall_data
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_pos_x;
	int		map_pos_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	double	d_dist_x;
	double	d_dist_y;
	int		side;
	double	perp_wall_dist;
	int		lineheight;
	int		draw_start;
	int		draw_end;
	double	wallx;
	int		tex_x;
	double	step_val;
	double	tex_pos;
	int		hit;
}				t_wall_data;

typedef struct	s_path
{
	char	*path_n;
	char	*path_s;
	char	*path_w;
	char	*path_e;
}				t_path;

/* main struct */
typedef struct	s_info
{
	void	*mlx;
	void	*win;
	int		win_wid;
	int		win_hei;
	int		buf[640][480];
	int		floor_color;
	int		ceiling_color;
	int		**texture;
	t_pos	*pos;
	t_key	*key;
	t_img	*img;
	t_path  *path;
	t_map	*map;
}				t_info;

/* 일단 들고온 list
typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
*/

/* Cub3D.c */
int		key_press(int key, t_info *info);
int		key_release(int key, t_info *info);
int		close_win(int keycode, int x, int y, void *param);
void	check_leaks();

/* calc_wall */
void	floor_cast(t_info *info);
void	init_dda_cast(t_wall_data *wall_data, t_info *info);
void	calc_perp_dist(t_wall_data *wall_data, t_info *info);
void	set_dda(t_wall_data *wall_data, t_info *info, int cur_x);
void	wall_cast(t_info *info, t_wall_data *wall_data, int count);
void	step_progress_until_hit(t_wall_data *wall_data, t_info *info);

/* draw_floor */
void    draw(t_info *info);

/* loop_hook.c */
void	hook_set(t_info *info);
int		render(t_info *info);
void	cal_vec(t_info *info);
int		raycasting(t_info *info);

/* gnl */
size_t	utils_strlen(const char *s);
size_t	utils_strlcpy(char *dest, const char *src, size_t dstsize);
size_t	utils_strlcat(char *dest, const char *src, size_t dstsize);
char	*utils_strjoin(char *s1, char *s2);
char	*utils_strdup(const char *s1);
int		utils_strchr(char *string);
char	*utils_substr(char const *s, unsigned int start, size_t len);
int		utils_get_size(char *str, int idx);
int		gnl_split(char **string, char **line, int i);
int		gnl_return(char **string, char **line, int read_size);
int		get_next_line(int fd, char **line);

/* init.c */
int		init_map(t_info *info, char *map_name);
int		init_key(t_info *info);
int		init_player(t_info *info);
int		init_win_img(t_info *info);
int		init_info(t_info *info, char *argv);
t_info	*init_info_mlx(void);

/* map_parse.c */
int		utils_check_txt_path(char *line);
int		utils_check_txt_execute(char *path);
char	*utils_substr(char const *s, unsigned int start, size_t len);
int		utils_get_size(char *str, int idx);
char	*get_texture_path(char *line, int idx);
int		read_txt_path(char *line, int first, int second, int idx, t_info *info);
int		utils_check_color(char *line, int c, int idx);
int		get_rgb_value(char *line);
int		read_color(char *line, int c, int idx, t_info *info);
int		read_map_setting(char *line, int idx, t_info *info);
int		map_check(char *line, char **map, int idx, int gnl_ret);
int		read_map_sub(char *line, char **map, t_info *info, int gnl_ret);
char	*read_map(char *argv, t_info *info);

/* texture_set.c */
int		read_map_path(char *line, char fir, char sec, t_info *info);
int		texture_set(t_info *info, char *pth, int idx);
int		read_map_color(char *line, char fc, t_info *info);

/* mov_cal.c */
int		empty_chk_map(t_map *map, int x, int y);
int		rotate_left(t_info *info);
int		rotate_right(t_info *info);
// int		rotate_mouse(t_info *info);

/* movement.c */
int		player_move_front(t_info *info);
int		player_move_back(t_info *info);
int		rotate_left(t_info *info);
int		player_move_left(t_info *info);
int		player_move_right(t_info *info);

/* movement2.c */
int		rotate_right(t_info *info);
int		key_update(t_info *info);

/* utils */
char	**utils_split(char const *s, char c);
int		utils_atoi(const char *str);
void	utils_free_split(char **split_rgb);

/* utils2.c */
int		utils_white_space(char c);
int		utils_isprint(int c);
int		utils_isdigit(int c);
void	utils_bzero(void *s, size_t n);

/* wall_cast.c */
void	set_wall_data(t_wall_data *wall_data, t_info *info);
void	set_texture_data(t_wall_data *wall_data, t_info *info);
int		set_color(t_wall_data *wall_data, t_info *info);

/* load_texture.c */
void	init_texture(t_info *info);
void	load_texture(t_info *info);
void	load_image(t_info *info, int *texture, char *path, t_img *img);

/* loop_hook.c */
int		loop(t_info *info);
void	hook_set(t_info *info);

/* save_map.c */
char	**save_map(char *line_map, t_info *info);

/* flood_fill.c */
int	check_fill(t_info *info);
int	flood_fill(int pox, int poy, t_info *info);

/* get_direction.c */
void	get_direction(t_info *info, char **world_map, int hei, int wid);
void	set_south(t_info *info, int hei, int wid);
void	set_east(t_info *info, int hei, int wid);
void	set_west(t_info *info, int hei, int wid);
void	set_north(t_info *info, int hei, int wid);


# endif