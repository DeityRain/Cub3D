/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:10:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/04/30 15:40:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	has_rgb_format(const char *line)
{
	const char	*p;

	p = line + 1;
	while (*p && (*p == ' ' || *p == '\t'))
		p++;
	while (*p)
	{
		if (*p == ',')
			return (1);
		if (*p == '\n' || *p == '\r')
			break ;
		p++;
	}
	return (0);
}

int	parse_floor_directive(t_map *map, const char *line, int *parsed)
{
	char	*value;

	if (!map || !line || !parsed)
		return (0);
	if (has_rgb_format(line))
		return (parse_floor_color(map, line, parsed));
	value = get_value_after_key(line, 1);
	if (!value)
		return (0);
	map->floor_tex_path = value;
	(*parsed)++;
	return (1);
}

int	parse_ceiling_directive(t_map *map, const char *line, int *parsed)
{
	char	*value;

	if (!map || !line || !parsed)
		return (0);
	if (has_rgb_format(line))
		return (parse_ceiling_color(map, line, parsed));
	value = get_value_after_key(line, 1);
	if (!value)
		return (0);
	map->ceil_tex_path = value;
	(*parsed)++;
	return (1);
}

/*
** find_map_bounds: Locates map start and end indices.
*/
int	find_map_bounds(char **lines, int count, int *start, int *end)
{
	*start = 0;
	while (*start < count && is_line_empty(lines[*start]))
		(*start)++;
	if (*start >= count)
		return (0);
	*end = count - 1;
	while (*end >= *start && is_line_empty(lines[*end]))
		(*end)--;
	return (*end >= *start);
}
