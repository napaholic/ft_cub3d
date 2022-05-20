/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:51:55 by yeju              #+#    #+#             */
/*   Updated: 2022/05/20 11:03:59 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void	check_leaks()
{
	system("leaks Cub3D");
	return ;
}

int	main(int argc, char **argv)
{
	t_info	*info;

	if (argc != 2)
	{
		printf("%s", "usage: ./Cub3D './map/path'");
		return (0);
	}
	info = init_info_mlx();
	if (!info)
		exit(1);
	if (!init_info(info, argv[1]))
	{
		printf("Error\n init error");
		exit(1);
	}
	load_texture(info);
	hook_set(info);
	atexit(check_leaks);
	return (0);
}