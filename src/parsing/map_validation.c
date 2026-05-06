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
** strip_line: Removes trailing newlines from duplicated string.
*/
static char	*strip_line(const char *s)
{
	char	*dup;
	int		len;

	dup = ft_strdup(s);
	if (!dup)
		return (NULL);
	len = ft_strlen(dup);
	while (len > 0 && (dup[len - 1] == '\n' || dup[len - 1] == '\r'))
		dup[--len] = '\0';
	return (dup);
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
			return (free(grid), NULL);
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

	r = 0;
	players = 0;
	while (r < map->height)
	{
		c = 0;
		while (map->grid[r][c])
		{
			if (!(map->grid[r][c] == '0' || map->grid[r][c] == '1'
				|| map->grid[r][c] == ' ' || map->grid[r][c] == 'N'
				|| map->grid[r][c] == 'S' || map->grid[r][c] == 'E'
				|| map->grid[r][c] == 'W'))
				return (0);
			if (map->grid[r][c] == 'N' || map->grid[r][c] == 'S'
				|| map->grid[r][c] == 'E' || map->grid[r][c] == 'W')
				players++;
			c++;
		}
		r++;
	}
	return (players == 1);
}
