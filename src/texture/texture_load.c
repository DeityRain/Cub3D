/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:02:35 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/07 14:02:36 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_one_texture(t_data *data, int index, char *path)
{
	char	full_path[512];
	char	*cwd;

	if (!path)
		return (0);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (0);
	if (path[0] == '.')
	{
		if (path[1] == '/')
			snprintf(full_path, sizeof(full_path), "%s/%s", cwd, path + 2);
		else
			snprintf(full_path, sizeof(full_path), "%s/%s", cwd, path);
	}
	else
		snprintf(full_path, sizeof(full_path), "%s/%s", cwd, path);
	free(cwd);
	data->tex[index].img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, full_path,
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
	int	loaded;

	loaded = 0;
	if (load_one_texture(data, 0, data->map.no_path))
		loaded++;
	if (load_one_texture(data, 1, data->map.so_path))
		loaded++;
	if (load_one_texture(data, 2, data->map.we_path))
		loaded++;
	if (load_one_texture(data, 3, data->map.ea_path))
		loaded++;
	if (loaded < 4)
		ft_putendl_fd("Warning: Some textures failed to load, using fallback colors", 2);
	return (1);
}

static int	load_texture_to(t_texture *tex, void *mlx_ptr, char *path)
{
	char    full_path[512];
	char    *cwd;

	if (!path)
		return (0);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (0);
	if (path[0] == '.')
	{
		if (path[1] == '/')
			snprintf(full_path, sizeof(full_path), "%s/%s", cwd, path + 2);
		else
			snprintf(full_path, sizeof(full_path), "%s/%s", cwd, path);
	}
	else
		snprintf(full_path, sizeof(full_path), "%s/%s", cwd, path);
	free(cwd);
	tex->img_ptr = mlx_xpm_file_to_image(mlx_ptr, full_path, &tex->width, &tex->height);
	if (!tex->img_ptr)
		return (0);
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	if (!tex->addr)
		return (0);
	return (1);
}

int	load_all_textures(t_data *data)
{
	int ok;

	ok = load_wall_texture(data);
	if (data->map.floor_tex_path)
		load_texture_to(&data->floor_tex, data->mlx_ptr, data->map.floor_tex_path);
	if (data->map.ceil_tex_path)
		load_texture_to(&data->ceil_tex, data->mlx_ptr, data->map.ceil_tex_path);
	return (ok);
}
