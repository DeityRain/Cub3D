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

extern int	parse_no_texture(t_map *map, const char *line, int *parsed);
extern int	parse_so_texture(t_map *map, const char *line, int *parsed);
extern int	parse_we_texture(t_map *map, const char *line, int *parsed);
extern int	parse_ea_texture(t_map *map, const char *line, int *parsed);
extern int	parse_floor_color(t_map *map, const char *line, int *parsed);
extern int	parse_ceiling_color(t_map *map, const char *line, int *parsed);
extern int	parse_floor_texture(t_map *map, const char *line, int *parsed);
extern int	parse_ceil_texture(t_map *map, const char *line, int *parsed);
extern int	is_line_empty(const char *s);
extern int	is_map_line(const char *s);

/*
** parse_header_line: Routes header line to appropriate parser.
*/
int	parse_header_line(t_map *map, const char *line, int *parsed)
{
	if (!line || !parsed || !map)
		return (0);
	if (ft_strncmp(line, "NO", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
		return (parse_no_texture(map, line, parsed));
	if (ft_strncmp(line, "SO", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
		return (parse_so_texture(map, line, parsed));
	if (ft_strncmp(line, "WE", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
		return (parse_we_texture(map, line, parsed));
	if (ft_strncmp(line, "EA", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
		return (parse_ea_texture(map, line, parsed));
	if (ft_strncmp(line, "FT", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
		return (parse_floor_texture(map, line, parsed));
	if (ft_strncmp(line, "CT", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
		return (parse_ceil_texture(map, line, parsed));
	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
		return (parse_floor_color(map, line, parsed));
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		return (parse_ceiling_color(map, line, parsed));
	return (0);
}

/*
** parse_header: Processes header section until 8 tokens or map found.
*/
int	parse_header(char **lines, int count, int *idx, t_map *map)
{
	int	parsed;

	parsed = 0;
	while (*idx < count && parsed < 8)
	{
		if (!is_line_empty(lines[*idx]))
		{
			if (is_map_line(lines[*idx]))
				break ;
			if (!parse_header_line(map, lines[*idx], &parsed))
				return (0);
		}
		(*idx)++;
	}
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
