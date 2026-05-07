/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extraction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 10:50:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/04 15:05:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int	validate_map_chars(t_map *map);
extern int	parse_header(char **lines, int count, int *idx, t_map *map);
extern int	find_map_bounds(char **lines, int count, int *start, int *end);
extern char	**collect_map_lines(char **lines, int start, int height, int *w);
extern void	free_lines_array(char **arr, int count);

static char	*get_map_base_dir(const char *filename)
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
static void	init_map(t_map *map)
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
** load_and_setup_map: Reads file, parses header and builds initial grid.
*/
static int	load_and_setup_map(const char *filename, t_map *map,
	int *start, int *end)
{
	char	**lines;
	int		count;
	int		i;
	int		h;

	if (!read_map_file(filename, &lines, &count))
		return (0);
	init_map(map);
	map->base_dir = get_map_base_dir(filename);
	if (!map->base_dir)
		return (free_lines_array(lines, count), 0);
	i = 0;
	if (!parse_header(lines, count, &i, map))
		return (free_lines_array(lines, count), 0);
	if (!find_map_bounds(lines, count, start, end))
		return (free_lines_array(lines, count), 0);
	h = *end - i + 1;
	map->grid = collect_map_lines(lines, i, h, &map->width);
	if (!map->grid)
		return (free_lines_array(lines, count), free_map(map), 0);
	map->height = h;
	free_lines_array(lines, count);
	return (1);
}

/*
** finalize_parsed_map: Runs validations, padding and player extraction.
*/
static int	finalize_parsed_map(t_map *map)
{
	if (!validate_map_chars(map))
	{
		ft_putendl_fd("Error: invalid characters in map", 2);
		return (free_map(map), 0);
	}
	if (!check_map_enclosed(map))
	{
		ft_putendl_fd("Error: map not enclosed", 2);
		return (free_map(map), 0);
	}
	if (!pad_map_grid(map))
	{
		ft_putendl_fd("Error: failed to pad map", 2);
		return (free_map(map), 0);
	}
	if (!extract_player_data(map))
	{
		ft_putendl_fd("Error: missing or multiple player positions", 2);
		return (free_map(map), 0);
	}
	return (1);
}

/*
** parse_cub_file: Main parser for .cub map file.
*/
int	parse_cub_file(const char *filename, t_map *map)
{
	int		start;
	int		end;

	if (!filename || !map)
		return (0);
	if (!load_and_setup_map(filename, map, &start, &end))
		return (0);
	if (!finalize_parsed_map(map))
		return (0);
	return (1);
}

/*
** free_map: Frees all allocated map resources.
*/
void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
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
	if (map->grid)
	{
		i = 0;
		while (map->grid[i])
			free(map->grid[i++]);
		free(map->grid);
	}
	init_map(map);
}
