/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_enclosure.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:40:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/04 16:40:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** free_grid_copy: Frees copied grid used for flood-fill validation.
*/
static void	free_grid_copy(char **grid, int height)
{
	while (height > 0)
		free(grid[--height]);
	free(grid);
}

/*
** copy_grid: Duplicates map grid for destructive flood-fill.
*/
static char	**copy_grid(t_map *map)
{
	char	**copy;
	int		r;

	if (!map || !map->grid || map->height <= 0)
		return (NULL);
	copy = malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		return (NULL);
	r = 0;
	while (r < map->height)
	{
		if (!map->grid[r])
			return (free_grid_copy(copy, r), NULL);
		copy[r] = ft_strdup(map->grid[r]);
		if (!copy[r])
			return (free_grid_copy(copy, r), NULL);
		r++;
	}
	copy[r] = NULL;
	return (copy);
}

/*
** is_walkable: Returns true for tiles reachable by player movement.
*/
static int	is_walkable(char ch)
{
	return (ch == '0' || ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W');
}

/*
** flood_fill_ok: Flood-fills reachable area and fails if void is touched.
*/
static int	flood_fill_ok(char **grid, int r, int c)
{
	if (r < 0 || c < 0 || !grid[r] || !grid[r][c])
		return (0);
	if (grid[r][c] == ' ')
		return (0);
	if (!is_walkable(grid[r][c]))
		return (1);
	grid[r][c] = 'V';
	if (!flood_fill_ok(grid, r + 1, c))
		return (0);
	if (!flood_fill_ok(grid, r - 1, c))
		return (0);
	if (!flood_fill_ok(grid, r, c + 1))
		return (0);
	return (flood_fill_ok(grid, r, c - 1));
}

/*
** check_map_enclosed: Validates map is closed around reachable area.
*/
int	check_map_enclosed(t_map *map)
{
	char	**copy;
	int		row;
	int		col;

	if (!map || !map->grid || map->height <= 0)
		return (0);
	copy = copy_grid(map);
	if (!copy)
		return (0);
	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (copy[row][col])
		{
			if (is_walkable(copy[row][col]))
			{
				if (!flood_fill_ok(copy, row, col))
					return (free_grid_copy(copy, map->height), 0);
			}
			col++;
		}
		row++;
	}
	free_grid_copy(copy, map->height);
	return (1);
}
