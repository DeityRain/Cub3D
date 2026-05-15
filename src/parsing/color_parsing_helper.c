/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 11:40:28 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/15 11:40:35 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	map->ceil_rgb[0] = out[0];
	map->ceil_rgb[1] = out[1];
	map->ceil_rgb[2] = out[2];
	(*parsed)++;
	return (1);
}
