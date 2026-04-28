#ifndef CUB3D_H
#define CUB3D_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>

//Linux Keycodes
# define KC_ESC 65307

typedef struct s_data {
	void	*mlx_ptr;
	void	*win_ptr;
} t_data;

typedef struct s_img {
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
} t_imgl;

typedef struct s_player {
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
} t_player;

typedef struct s_map {
	char	*no_path;	// north texture
	char	*so_path;	// south texture
	char	*we_path;	//west texture
	char	*ea_texture;	//east texture
	int		floor_rgb[3];
	int		ceiling_rgb[3];
	char	**grid;		//2D map Array
	int		height;
	int		widthl
}	t_map;

int    close_window(t_data *data);
int    handle_keypress(int keysym, t_data *data);

#endif