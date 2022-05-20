/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:51:55 by yeju              #+#    #+#             */
/*   Updated: 2022/05/20 11:43:31 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

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
	return (0);
}
