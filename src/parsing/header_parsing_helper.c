/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_parsing_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:10:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/04/30 15:40:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int	parse_floor_directive(t_map *map, const char *line, int *parsed);
extern int	parse_ceiling_directive(t_map *map, const char *line, int *parsed);

static int	parse_header_directive(t_map *map, const char *line,
				int *parsed)
{
	if (ft_strncmp(line, "NO", 2) == 0
		&& (line[2] == ' ' || line[2] == '\t'))
		return (parse_no_texture(map, line, parsed));
	if (ft_strncmp(line, "SO", 2) == 0
		&& (line[2] == ' ' || line[2] == '\t'))
		return (parse_so_texture(map, line, parsed));
	if (ft_strncmp(line, "WE", 2) == 0
		&& (line[2] == ' ' || line[2] == '\t'))
		return (parse_we_texture(map, line, parsed));
	if (ft_strncmp(line, "EA", 2) == 0
		&& (line[2] == ' ' || line[2] == '\t'))
		return (parse_ea_texture(map, line, parsed));
	if (ft_strncmp(line, "FT", 2) == 0
		&& (line[2] == ' ' || line[2] == '\t'))
		return (parse_floor_texture(map, line, parsed));
	if (ft_strncmp(line, "CT", 2) == 0
		&& (line[2] == ' ' || line[2] == '\t'))
		return (parse_ceil_texture(map, line, parsed));
	if (line[0] == 'F'
		&& (line[1] == ' ' || line[1] == '\t'))
		return (parse_floor_directive(map, line, parsed));
	if (line[0] == 'C'
		&& (line[1] == ' ' || line[1] == '\t'))
		return (parse_ceiling_directive(map, line, parsed));
	return (0);
}

/*
** parse_header_line: Routes header line to appropriate parser.
*/
int	parse_header_line(t_map *map, const char *line, int *parsed)
{
	int	result;

	if (!line || !parsed || !map)
		return (0);
	result = parse_header_directive(map, line, parsed);
	if (!result)
		ft_putendl_fd("Error: invalid or duplicate header key", 2);
	return (result);
}

/*
** parse_header: Processes header section until 6 tokens or map found.
*/
int	parse_header(char **lines, int count, int *idx, t_map *map)
{
	int	parsed;

	parsed = 0;
	while (*idx < count && parsed < 6)
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
