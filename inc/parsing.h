#ifndef PARSING_H
#define PARSING_H

int	validate_file(const char *filename);
int read_map_file(const char *filename, char ***lines, int *count);
int parse_cub_file(const char *filename, t_map *map);
int	pad_map_grid(t_map *map);
int	extract_player_data(t_map *map);
int	check_map_enclosed(t_map *map);
void free_map(t_map *map);

#endif
