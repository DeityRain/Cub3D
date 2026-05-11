/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 09:30:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/03 16:20:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_lines_array(char **arr, int count);

/*
** is_line_empty: Checks if line contains only whitespace.
*/
int	is_line_empty(const char *s)
{
	if (!s)
		return (1);
	while (*s)
	{
		if (!(*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n'))
			return (0);
		s++;
	}
	return (1);
}

/*
** is_map_line: Checks if line contains only valid map characters.
*/
int	is_map_line(const char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == ' ' || *s == '\t' || *s == '\r'
			|| *s == '\n')
		{
			s++;
			continue ;
		}
		if (*s == '0' || *s == '1' || *s == 'N' || *s == 'S'
			|| *s == 'E' || *s == 'W')
		{
			s++;
			continue ;
		}
		return (0);
	}
	return (1);
}

/*
** collect_map_lines: Allocates and copies map lines into grid array.
*/
char	**collect_map_lines(char **lines, int start, int height, int *width)
{
	char	**grid;
	int		r;

	grid = malloc(sizeof(char *) * (height + 1));
	if (!grid)
		return (NULL);
	*width = 0;
	r = 0;
	while (r < height)
	{
		grid[r] = strip_line(lines[start + r]);
		if (!grid[r])
		{
			while (r > 0)
				free(grid[--r]);
			free(grid);
			return (NULL);
		}
		if ((int)ft_strlen(grid[r]) > *width)
			*width = ft_strlen(grid[r]);
		r++;
	}
	grid[height] = NULL;
	return (grid);
}

/*
** validate_map_chars: Checks map contains only valid characters.
*/
int	validate_map_chars(t_map *map)
{
	int	r;
	int	c;
	int	players;

	if (!map || !map->grid || map->height <= 0)
		return (0);
	r = 0;
	players = 0;
	while (r < map->height)
	{
		if (!map->grid[r])
			return (0);
		c = 0;
		while (map->grid[r][c])
		{
			if (!is_valid_map_char(map->grid[r][c]))
				return (0);
			if (is_player_char(map->grid[r][c]))
				players++;
			c++;
		}
		r++;
	}
	return (players == 1);
}
