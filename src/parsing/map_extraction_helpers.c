/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extraction_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 10:50:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/04 15:05:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** get_map_base_dir: Extracts directory path from filename.
*/
char	*get_map_base_dir(const char *filename)
{
	char		*slash;
	size_t		dir_len;

	slash = ft_strrchr(filename, '/');
	if (!slash)
		return (ft_strdup("."));
	dir_len = slash - filename;
	if (dir_len == 0)
		return (ft_strdup("/"));
	return (ft_substr(filename, 0, dir_len));
}

/*
** init_map: Initializes all map struct fields to NULL/0.
*/
void	init_map(t_map *map)
{
	map->no_path = NULL;
	map->so_path = NULL;
	map->we_path = NULL;
	map->ea_path = NULL;
	map->floor_tex_path = NULL;
	map->ceil_tex_path = NULL;
	map->base_dir = NULL;
	map->floor_rgb[0] = 211;
	map->floor_rgb[1] = 211;
	map->floor_rgb[2] = 211;
	map->ceil_rgb[0] = 135;
	map->ceil_rgb[1] = 206;
	map->ceil_rgb[2] = 235;
	map->grid = NULL;
	map->height = 0;
	map->width = 0;
	map->player_x = 0.0;
	map->player_y = 0.0;
	map->dir_x = 0.0;
	map->dir_y = 0.0;
	map->plane_x = 0.0;
	map->plane_y = 0.0;
	map->player_dir = 0;
}

/*
** free_map_paths: Frees all texture and base directory paths.
*/
void	free_map_paths(t_map *map)
{
	if (map->no_path)
		free(map->no_path);
	if (map->so_path)
		free(map->so_path);
	if (map->we_path)
		free(map->we_path);
	if (map->ea_path)
		free(map->ea_path);
	if (map->floor_tex_path)
		free(map->floor_tex_path);
	if (map->ceil_tex_path)
		free(map->ceil_tex_path);
	if (map->base_dir)
		free(map->base_dir);
}
