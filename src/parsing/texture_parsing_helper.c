/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:05:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/01 11:55:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* get_value_after_key: Extracts value after header key + whitespace. */
static char	*get_value_after_key(const char *line, int key_len)
{
	const char	*p;
	char		*value;

	p = line + key_len;
	while (*p && (*p == ' ' || *p == '\t'))
		p++;
	value = ft_strtrim(p, " \t\n");
	return (value);
}

/* parse_floor_texture: optional FT path */
int	parse_floor_texture(t_map *map, const char *line, int *parsed)
{
	(void)parsed;
	if (map->floor_tex_path)
		return (0);
	map->floor_tex_path = get_value_after_key(line, 2);
	if (!map->floor_tex_path)
		return (0);
	return (1);
}

/* parse_ceil_texture: optional CT path */
int	parse_ceil_texture(t_map *map, const char *line, int *parsed)
{
	(void)parsed;
	if (map->ceil_tex_path)
		return (0);
	map->ceil_tex_path = get_value_after_key(line, 2);
	if (!map->ceil_tex_path)
		return (0);
	return (1);
}
