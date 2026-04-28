#ifndef CUB3D_H
#define CUBD_H

# include "../minilibx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

//Linux Keycodes
# define KC_ESC 65307

typedef struct s_img {
	void	*img_ptr;
	char	*addr;
	int	bits_per_pixel;
	int	line_lenght;
	int	endian;
} t_imgl;

typedef struct s_player {
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
} t_player;

int    close_window(t_data *data);
int    handle_keypress(int keysym, t_data *data);

#endif