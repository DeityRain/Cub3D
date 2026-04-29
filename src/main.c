#include "cub3d.h"
#include "parsing.h"

// 2. The function that actually closes the window
int close_window(t_data *data)
{
    printf("Cleaning up and exiting...\n");
    free_map(&data->map);
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    free(data->mlx_ptr);
    exit(0);
    return (0);
}

// 3. The function that checks which key was pressed
int handle_keypress(int keysym, t_data *data)
{
    if (keysym == KC_ESC)
        close_window(data);
    return (0);
}

int main(int ac, char **av)
{
    t_data  data;

    if (ac != 2)
    {
        printf("Usage: ./cub3D <map.cub>\n");
        return (1);
    }
    if (!validate_file(av[1]))
        return (1);

    if (!parse_cub_file(av[1], &data.map))
    {
        printf("Error: failed to parse map file\n");
        return (1);
    }

    data.mlx_ptr = mlx_init();
    if (!data.mlx_ptr)
    {
        free_map(&data.map);
        return (1);
    }

    data.win_ptr = mlx_new_window(data.mlx_ptr, 800, 600, "cub3D");
    if (!data.win_ptr)
    {
        free_map(&data.map);
        free(data.mlx_ptr);
        return (1);
    }

    mlx_key_hook(data.win_ptr, handle_keypress, &data);
    mlx_hook(data.win_ptr, 17, 0, close_window, &data);

    mlx_loop(data.mlx_ptr);
    return (0);
}
