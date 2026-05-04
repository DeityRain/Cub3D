/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_padding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:35:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/04 16:00:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

/*
** free_partial_grid: Frees allocated rows in temporary padded grid.
*/
static void	free_partial_grid(char **grid, int count)
{
	while (count > 0)
		free(grid[--count]);
	free(grid);
}

/*
** make_wall_row: Creates one full wall row filled with '1'.
*/
static char	*make_wall_row(int width)
{
	char	*row;

	row = malloc(sizeof(char) * (width + 1));
	if (!row)
		return (NULL);
	ft_memset(row, '1', width);
	row[width] = '\0';
	return (row);
}

/*
** make_inner_row: Creates padded row with side walls and map contents.
*/
static char	*make_inner_row(const char *src, int width)
{
	char	*row;
	int		i;

	row = malloc(sizeof(char) * (width + 3));
	if (!row)
		return (NULL);
	row[0] = '1';
	i = 0;
	while (i < width)
	{
		if (src[i])
			row[i + 1] = src[i];
		else
			row[i + 1] = ' ';
		i++;
	}
	row[i + 1] = '1';
	row[i + 2] = '\0';
	return (row);
}

/*
** set_padded_map: Replaces old grid by padded one and updates dimensions.
*/
static void	set_padded_map(t_map *map, char **new_grid)
{
	free_partial_grid(map->grid, map->height);
	map->grid = new_grid;
	map->height += 2;
	map->width += 2;
}

/*
** pad_map_grid: Builds a new map grid padded by wall border.
*/
int	pad_map_grid(t_map *map)
{
	char	**new_grid;
	int		r;

	new_grid = malloc(sizeof(char *) * (map->height + 3));
	if (!new_grid)
		return (0);
	new_grid[0] = make_wall_row(map->width + 2);
	if (!new_grid[0])
		return (free(new_grid), 0);
	r = 0;
	while (r < map->height)
	{
		new_grid[r + 1] = make_inner_row(map->grid[r], map->width);
		if (!new_grid[r + 1])
			return (free_partial_grid(new_grid, r + 1), 0);
		r++;
	}
	new_grid[r + 1] = make_wall_row(map->width + 2);
	if (!new_grid[r + 1])
		return (free_partial_grid(new_grid, r + 1), 0);
	new_grid[r + 2] = NULL;
	set_padded_map(map, new_grid);
	return (1);
}
