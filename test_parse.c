#include <stdio.h>
#include "inc/cub3d.h"
#include "inc/parsing.h"

int main(void)
{
    t_map map;
    const char *path = "maps/miniMap.cub";

    if (!parse_cub_file(path, &map))
    {
        printf("parse_cub_file failed\n");
        return 1;
    }

    printf("Parsed map: height=%d width=%d\n", map.height, map.width);
    printf("NO: %s\n", map.no_path ? map.no_path : "(null)");
    printf("SO: %s\n", map.so_path ? map.so_path : "(null)");
    printf("WE: %s\n", map.we_path ? map.we_path : "(null)");
    printf("EA: %s\n", map.ea_texture ? map.ea_texture : "(null)");
    printf("Floor RGB: %d,%d,%d\n", map.floor_rgb[0], map.floor_rgb[1], map.floor_rgb[2]);
    printf("Ceil RGB: %d,%d,%d\n", map.ceiling_rgb[0], map.ceiling_rgb[1], map.ceiling_rgb[2]);

    for (int i = 0; i < map.height; ++i)
        printf("%s\n", map.grid[i]);

    free_map(&map);
    return 0;
}
