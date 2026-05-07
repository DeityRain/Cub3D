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

/*
** get_value_after_key: Extracts value after header key + whitespace.
*/
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

/*
** parse_no_texture: Parses NO (north) texture path.
*/
int	parse_no_texture(t_map *map, const char *line, int *parsed)
{
	if (map->no_path)
		return (0);
	map->no_path = get_value_after_key(line, 2);
	if (!map->no_path)
		return (0);
	(*parsed)++;
	return (1);
}

/*
** parse_so_texture: Parses SO (south) texture path.
*/
int	parse_so_texture(t_map *map, const char *line, int *parsed)
{
	if (map->so_path)
		return (0);
	map->so_path = get_value_after_key(line, 2);
	if (!map->so_path)
		return (0);
	(*parsed)++;
	return (1);
}

/*
** parse_we_texture: Parses WE (west) texture path.
*/
int	parse_we_texture(t_map *map, const char *line, int *parsed)
{
	if (map->we_path)
		return (0);
	map->we_path = get_value_after_key(line, 2);
	if (!map->we_path)
		return (0);
	(*parsed)++;
	return (1);
}

/*
** parse_ea_texture: Parses EA (east) texture path.
*/
int	parse_ea_texture(t_map *map, const char *line, int *parsed)
{
	if (map->ea_path)
		return (0);
	map->ea_path = get_value_after_key(line, 2);
	if (!map->ea_path)
		return (0);
	(*parsed)++;
	return (1);
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
	/* do not increment parsed: optional */
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
	/* do not increment parsed: optional */
	return (1);
}
