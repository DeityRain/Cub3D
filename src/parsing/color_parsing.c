/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:25:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/02 14:10:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** free_split: Frees array of strings from ft_split.
*/
static void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

/*
** validate_rgb_values: Validates and assigns RGB values from parts array.
*/
static int	validate_rgb_values(char **parts, int out[3])
{
	int	i;
	int	val;

	i = 0;
	while (i < 3)
	{
		val = ft_atoi(parts[i]);
		if (val < 0 || val > 255)
			return (0);
		out[i] = val;
		i++;
	}
	return (1);
}

/*
** parse_color: Parses "R,G,B" format into 3 integers [0-255].
*/
static int	parse_color(const char *s, int out[3])
{
	char	*trimmed;
	char	**parts;
	int		i;

	if (!s)
		return (0);
	trimmed = ft_strtrim(s, " \t");
	if (!trimmed)
		return (0);
	parts = ft_split(trimmed, ',');
	free(trimmed);
	if (!parts)
		return (0);
	i = 0;
	while (parts[i])
		i++;
	if (i != 3)
		return (free_split(parts), 0);
	if (!validate_rgb_values(parts, out))
		return (free_split(parts), 0);
	free_split(parts);
	return (1);
}

/*
** parse_floor_color: Parses F floor color (R,G,B).
*/
int	parse_floor_color(t_map *map, const char *line, int *parsed)
{
	int	out[3];

	if (!parse_color(line + 1, out))
		return (0);
	map->floor_rgb[0] = out[0];
	map->floor_rgb[1] = out[1];
	map->floor_rgb[2] = out[2];
	(*parsed)++;
	return (1);
}

/*
** parse_ceiling_color: Parses C ceiling color (R,G,B).
*/
int	parse_ceiling_color(t_map *map, const char *line, int *parsed)
{
	int	out[3];

	if (!parse_color(line + 1, out))
		return (0);
	map->ceiling_rgb[0] = out[0];
	map->ceiling_rgb[1] = out[1];
	map->ceiling_rgb[2] = out[2];
	(*parsed)++;
	return (1);
}
