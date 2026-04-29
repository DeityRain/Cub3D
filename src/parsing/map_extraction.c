#include "cub3d.h"
#include "parsing.h"

#include <ctype.h>

static void free_split(char **arr)
{
	int i = 0;
	if (!arr)
		return;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static int parse_color(const char *s, int out[3])
{
	char *trimmed;
	char **parts;
	int i;

	if (!s)
		return 0;
	trimmed = ft_strtrim(s, " \t");
	if (!trimmed)
		return 0;
	parts = ft_split(trimmed, ',');
	free(trimmed);
	if (!parts)
		return 0;
	i = 0;
	while (parts[i])
		i++;
	if (i != 3)
	{
		free_split(parts);
		return 0;
	}
	for (i = 0; i < 3; ++i)
	{
		int val = ft_atoi(parts[i]);
		if (val < 0 || val > 255)
		{
			free_split(parts);
			return 0;
		}
		out[i] = val;
	}
	free_split(parts);
	return 1;
}

static char *get_value_after_key(const char *line, int key_len)
{
	const char *p = line + key_len;
	while (*p && (*p == ' ' || *p == '\t'))
		++p;
	return ft_strdup(p);
}

static int parse_header_line(t_map *map, const char *line, int *parsed)
{
	if (!line || !parsed || !map)
		return 0;
	if (ft_strncmp(line, "NO", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
	{
		if (map->no_path)
			return 0;
		map->no_path = get_value_after_key(line, 2);
		if (!map->no_path) return 0;
		(*parsed)++;
		return 1;
	}
	if (ft_strncmp(line, "SO", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
	{
		if (map->so_path) return 0;
		map->so_path = get_value_after_key(line, 2);
		if (!map->so_path) return 0;
		(*parsed)++;
		return 1;
	}
	if (ft_strncmp(line, "WE", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
	{
		if (map->we_path) return 0;
		map->we_path = get_value_after_key(line, 2);
		if (!map->we_path) return 0;
		(*parsed)++;
		return 1;
	}
	if (ft_strncmp(line, "EA", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
	{
		if (map->ea_texture) return 0;
		map->ea_texture = get_value_after_key(line, 2);
		if (!map->ea_texture) return 0;
		(*parsed)++;
		return 1;
	}
	if ((line[0] == 'F' || line[0] == 'C') && (line[1] == ' ' || line[1] == '\t'))
	{
		int out[3];
		if (line[0] == 'F')
		{
			if (!parse_color(line + 1, out)) return 0;
			map->floor_rgb[0] = out[0];
			map->floor_rgb[1] = out[1];
			map->floor_rgb[2] = out[2];
			(*parsed)++;
			return 1;
		}
		else
		{
			if (!parse_color(line + 1, out)) return 0;
			map->ceiling_rgb[0] = out[0];
			map->ceiling_rgb[1] = out[1];
			map->ceiling_rgb[2] = out[2];
			(*parsed)++;
			return 1;
		}
	}
	return 0;
}

static int is_line_empty(const char *s)
{
	if (!s) return 1;
	while (*s)
	{
		if (!(*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n'))
			return 0;
		++s;
	}
	return 1;
}

static int is_map_line(const char *s)
{
	if (!s) return 0;
	while (*s)
	{
		if (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n') { ++s; continue; }
		if (*s == '0' || *s == '1' || *s == 'N' || *s == 'S' || *s == 'E' || *s == 'W') { ++s; continue; }
		return 0;
	}
	return 1;
}

int parse_cub_file(const char *filename, t_map *map)
{
	char **lines = NULL;
	int count = 0;
	int i = 0;
	int parsed = 0;

	if (!filename || !map) return 0;
	if (!read_map_file(filename, &lines, &count)) return 0;

	/* init map */
	map->no_path = NULL;
	map->so_path = NULL;
	map->we_path = NULL;
	map->ea_texture = NULL;
	map->grid = NULL;
	map->height = 0;
	map->width = 0;

	/* parse header lines until we have 6 tokens or map found */
	while (i < count && parsed < 6)
	{
		if (!is_line_empty(lines[i]))
		{
			if (is_map_line(lines[i]))
				break;
			if (!parse_header_line(map, lines[i], &parsed))
			{
				for (int k = 0; k < count; ++k) free(lines[k]);
				free(lines);
				return 0;
			}
		}
		i++;
	}

	while (i < count && is_line_empty(lines[i])) i++;
	if (i >= count)
	{
		for (int k = 0; k < count; ++k) free(lines[k]);
		free(lines);
		return 0; /* no map data */
	}

	/* find last non-empty line */
	int end = count - 1;
	while (end >= i && is_line_empty(lines[end])) end--;
	if (end < i)
	{
		for (int k = 0; k < count; ++k) free(lines[k]);
		free(lines);
		return 0;
	}

	int h = end - i + 1;
	char **grid = malloc(sizeof(char *) * (h + 1));
	if (!grid)
	{
		for (int k = 0; k < count; ++k) free(lines[k]);
		free(lines);
		return 0;
	}
	int w = 0;
	for (int r = 0; r < h; ++r)
	{
		grid[r] = ft_strdup(lines[i + r]);
		if (grid[r])
		{
			int L = ft_strlen(grid[r]);
			while (L > 0 && (grid[r][L-1] == '\n' || grid[r][L-1] == '\r'))
			{
				grid[r][L-1] = '\0';
				--L;
			}
		}
		if (!grid[r])
		{
			for (int t = 0; t < r; ++t) free(grid[t]);
			free(grid);
			for (int k = 0; k < count; ++k) free(lines[k]);
			free(lines);
			return 0;
		}
		int len = ft_strlen(grid[r]);
		if (len > w) w = len;
	}
	grid[h] = NULL;

	/* cleanup lines array */
	for (int k = 0; k < count; ++k) free(lines[k]);
	free(lines);

	map->grid = grid;
	map->height = h;
	map->width = w;

	/* validation: allowed chars and exactly one player */
	int player_count = 0;
	for (int rr = 0; rr < map->height; ++rr)
	{
		for (int cc = 0; map->grid[rr][cc]; ++cc)
		{
			char c = map->grid[rr][cc];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W') player_count++;
			if (!(c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E' || c == 'W'))
			{
				free_map(map);
				return 0;
			}
		}
	}
	if (player_count != 1)
	{
		free_map(map);
		return 0;
	}

	return 1;
}

void free_map(t_map *map)
{
	if (!map) return;
	if (map->no_path) free(map->no_path);
	if (map->so_path) free(map->so_path);
	if (map->we_path) free(map->we_path);
	if (map->ea_texture) free(map->ea_texture);
	if (map->grid)
	{
		for (int i = 0; map->grid[i]; ++i)
			free(map->grid[i]);
		free(map->grid);
		map->grid = NULL;
	}
	map->height = 0;
	map->width = 0;
}