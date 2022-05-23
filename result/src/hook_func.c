/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:21:07 by yeju              #+#    #+#             */
/*   Updated: 2022/05/23 09:38:11 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	key_press(int key, t_info *info)
{
	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_W && info->key->w == 0)
		info->key->w = 1;
	else if (key == KEY_S && info->key->s == 0)
		info->key->s = 1;
	else if (key == KEY_A && info->key->a == 0)
		info->key->a = 1;
	else if (key == KEY_D && info->key->d == 0)
		info->key->d = 1;
	else if (key == KEY_LEFT && info->key->left == 0)
		info->key->left = 1;
	else if (key == KEY_RIGHT && info->key->right == 0)
		info->key->right = 1;
	return (1);
}

int	key_release(int key, t_info *info)
{
	if (key == KEY_W && info->key->w == 1)
		info->key->w = 0;
	else if (key == KEY_S && info->key->s == 1)
		info->key->s = 0;
	else if (key == KEY_A && info->key->a == 1)
		info->key->a = 0;
	else if (key == KEY_D && info->key->d == 1)
		info->key->d = 0;
	else if (key == KEY_LEFT && info->key->left == 1)
		info->key->left = 0;
	else if (key == KEY_RIGHT && info->key->right == 1)
		info->key->right = 0;
	return (1);
}

int	close_win(int keycode, int x, int y, void *param)
{
	(void)keycode;
	(void)x;
	(void)y;
	(void)param;
	exit(0);
}

int	render(t_info *info)
{
	if (!raycasting(info))
		print_exit("raycasting error");
	key_update(info);
	return (1);
}
