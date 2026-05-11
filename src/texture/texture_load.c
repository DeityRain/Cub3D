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

static int	make_full_path(char full_path[512], char *path)
{
	char	*cwd;
	char	*rel;

	if (!path)
		return (0);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (0);
	rel = path;
	if (path[0] == '.' && path[1] == '/')
		rel = path + 2;
	snprintf(full_path, 512, "%s/%s", cwd, rel);
	free(cwd);
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
		ft_putendl_fd("Warning: Some textures failed to load, "
			"using fallback colors", 2);
	return (1);
}

static int	load_texture_to(t_texture *tex, void *mlx_ptr, char *path)
{
	char	full_path[512];

	if (!make_full_path(full_path, path))
		return (0);
	tex->img_ptr = mlx_xpm_file_to_image(mlx_ptr, full_path, &tex->width,
			&tex->height);
	if (!tex->img_ptr)
		return (0);
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	if (!tex->addr)
	{
		mlx_destroy_image(mlx_ptr, tex->img_ptr);
		tex->img_ptr = NULL;
		return (0);
	}
	return (1);
}

int	load_one_texture(t_data *data, int index, char *path)
{
	if (!data || index < 0 || index >= 4)
		return (0);
	return (load_texture_to(&data->tex[index], data->mlx_ptr, path));
}

int	load_all_textures(t_data *data)
{
	int	ok;

	ok = load_wall_texture(data);
	if (data->map.floor_tex_path)
		load_texture_to(&data->floor_tex, data->mlx_ptr,
			data->map.floor_tex_path);
	if (data->map.ceil_tex_path)
		load_texture_to(&data->ceil_tex, data->mlx_ptr,
			data->map.ceil_tex_path);
	return (ok);
}
