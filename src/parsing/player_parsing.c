/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:25:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/04 16:25:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** set_player_dir: Sets direction and camera plane from orientation marker.
*/
static void	set_player_dir(t_map *map, char dir)
{
	if (dir == 'N')
		map->dir_y = -1.0;
	else if (dir == 'S')
		map->dir_y = 1.0;
	else if (dir == 'E')
		map->dir_x = 1.0;
	else
		map->dir_x = -1.0;
	if (dir == 'N' || dir == 'S')
		map->plane_x = 0.66 * -map->dir_y;
	else
		map->plane_y = 0.66 * map->dir_x;
}

/*
** set_player_at: Stores player data and replaces marker by floor tile.
*/
static void	set_player_at(t_map *map, int row, int col, char dir)
{
	map->player_x = col + 0.5;
	map->player_y = row + 0.5;
	map->player_dir = dir;
	map->dir_x = 0.0;
	map->dir_y = 0.0;
	map->plane_x = 0.0;
	map->plane_y = 0.0;
	set_player_dir(map, dir);
	map->grid[row][col] = '0';
}

/*
** extract_player_data: Finds player marker and stores position/vectors.
*/
int	extract_player_data(t_map *map)
{
	int	row;
	int	col;
	int	found;

	if (!map || !map->grid || map->height <= 0)
		return (0);
	row = 0;
	found = 0;
	while (row < map->height)
	{
		if (!map->grid[row])
			return (0);
		col = 0;
		while (map->grid[row][col])
		{
			if (is_player_char(map->grid[row][col]) && found++)
				return (0);
			if (is_player_char(map->grid[row][col]))
				set_player_at(map, row, col, map->grid[row][col]);
			col++;
		}
		row++;
	}
	return (found == 1);
}
