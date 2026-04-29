#include "cub3d.h"


/*
The map must be composed of only 6 possible characters: 0 for an empty space,
1 for a wall, and N,S,E or W for the player’s start position and spawning
orientation.
*/

int read_map_file(const char *filename, char ***lines, int *count)
{
    int fd;
    char *line;
    char **arr = NULL;
    int capacity = 0;
    int n = 0;

    if (!filename || !lines || !count)
        return 0;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return 0;

    capacity = 16;
    arr = malloc(sizeof(char *) * capacity);
    if (!arr)
    {
        close(fd);
        return 0;
    }

    while ((line = get_next_line(fd)))
    {
        if (n >= capacity)
        {
            int newcap = capacity * 2;
            char **tmp = realloc(arr, sizeof(char *) * newcap);
            if (!tmp)
            {
                free(line);
                for (int i = 0; i < n; ++i)
                    free(arr[i]);
                free(arr);
                close(fd);
                *lines = NULL;
                *count = 0;
                return 0;
            }
            arr = tmp;
            capacity = newcap;
        }
        arr[n++] = line;
    }

    close(fd);

    if (n >= capacity)
    {
        char **tmp = realloc(arr, sizeof(char *) * (n + 1));
        if (!tmp)
        {
            for (int i = 0; i < n; ++i)
                free(arr[i]);
            free(arr);
            *lines = NULL;
            *count = 0;
            return 0;
        }
        arr = tmp;
    }
    arr[n] = NULL;

    *lines = arr;
    *count = n;
    return 1;
}