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

	p = line + key_len;
	while (*p && (*p == ' ' || *p == '\t'))
		p++;
	return (ft_strdup(p));
}

/*
** parse_no_texture: Parses NO (north) texture path.
*/
int	parse_no_texture(t_map *map, const char *line, int *parsed)
{
	char	*val;
	char	*trimmed;

	if (map->no_path)
		return (0);
	val = ft_strdup(line + 2);
	if (!val)
		return (0);
	trimmed = val;
	while (*trimmed && (*trimmed == ' ' || *trimmed == '\t'))
		trimmed++;
	map->no_path = ft_strdup(trimmed);
	free(val);
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
	if (map->ea_texture)
		return (0);
	map->ea_texture = get_value_after_key(line, 2);
	if (!map->ea_texture)
		return (0);
	(*parsed)++;
	return (1);
}
