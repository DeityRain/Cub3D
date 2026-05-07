/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:02:35 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/07 14:02:36 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** load textures for wall (0=NO, 1=SO, 2=WE, 3=EA)
*/
int	load_one_texture(t_data *data, int index, char *path)
{
	if (!path)
		return (0);
	data->tex[index].img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,path,
		&data->tex[index].width, &data->tex[index].height);
	if (!data->tex[index].img_ptr)
		return (0);
	data->tex[index].addr = mlx_get_data_addr(
		data->tex[index].img_ptr,
		&data->tex[index].bits_per_pixel,
		&data->tex[index].line_length,
		&data->tex[index].endian);
	if (!data->tex[index].addr)
		return (0);
	return (1);
}

int	load_wall_texture(t_data *data)
{
	if (!load_one_texture(data, 0, data->map.no_path)
		|| !load_one_texture(data, 1, data->map.so_path)
		|| !load_one_texture(data, 2, data->map.we_path)
		|| !load_one_texture(data, 3, data->map.ea_path))
		return (0);
	return (1);
}