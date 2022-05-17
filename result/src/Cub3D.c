/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:51:55 by yeju              #+#    #+#             */
/*   Updated: 2022/05/13 14:29:45 by yeju             ###   ########.fr       */
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
	// 0. init
	info = init_info_mlx();
	if (!info)
		exit(1);
	// 1. map
	// 2. vector & mlx init, mlx_new_window
	// 3. textureLoad
	if (!init_info(info, argv[1]))
	{
		printf("Error\n init error");
		exit(1);
	}
	load_texture(info);
	// 4. mlx_hook
	hook_set(info);

	// 5. free & game end
	// render(info);
	// 6. leaks check
	atexit(check_leaks);
	return (0);
}