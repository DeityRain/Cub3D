#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

// 1. Define the Linux ESC keycode
#define KC_ESC 65307

typedef struct s_data {
    void    *mlx_ptr;
    void    *win_ptr;
} t_data;

// 2. The function that actually closes the window
int close_window(t_data *data)
{
    printf("Cleaning up and exiting...\n");
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    
    // On Linux, you should also destroy the display connection to avoid leaks
    // mlx_destroy_display(data->mlx_ptr); 
    
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

int main(void)
{
    t_data  data;

    data.mlx_ptr = mlx_init();
    if (!data.mlx_ptr)
        return (1);

    data.win_ptr = mlx_new_window(data.mlx_ptr, 800, 600, "cub3D");
    if (!data.win_ptr)
    {
        free(data.mlx_ptr);
        return (1);
    }

    // --- The Magic Hooks ---

    // Listen for the ESC key
    mlx_key_hook(data.win_ptr, handle_keypress, &data);

    // Listen for the "Red Cross" click (Event 17 is DestroyNotify)
    mlx_hook(data.win_ptr, 17, 0, close_window, &data);

    // -----------------------

    mlx_loop(data.mlx_ptr);
    return (0);
}
