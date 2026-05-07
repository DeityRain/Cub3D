/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 11:40:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/06 16:10:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// Linux Keycodes
# define ESC_KEY 65307

// Arrow keys (X11 keysyms)
# define LEFT_KEY 65361
# define UP_KEY 65362
# define RIGHT_KEY 65363
# define DOWN_KEY 65364

// WASD (ASCII keysyms)
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100

// Window Dimensions
# define WIN_WIDTH 800
# define WIN_HEIGHT 600

// Movement speeds
# define MOVE_SPEED 0.03
# define ROT_SPEED 0.03

/* ************************************************************************** */
/* Structures																  */
/* ************************************************************************** */

typedef struct s_map
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*floor_tex_path;
	char		*ceil_tex_path;
	int			floor_rgb[3];
	char		*base_dir;
	int			ceil_rgb[3];
	char		**grid;
	int			height;
	int			width;
	double		player_x;
	double		player_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	char		player_dir;
}				t_map;

typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

}				t_img;

typedef struct s_texture
{
    void    *img_ptr;
    char    *addr;
    int     width;
    int     height;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_texture;

/*0=NO, 1=SO, 2=WE, 3=EA*/
typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_map		map;
	 t_texture	floor_tex;
	 t_texture	ceil_tex;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_up;
	int			key_down;
	int			key_left;
	int			key_right;
	t_texture	tex[4];
}                t_data;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_dda
{
	double		pos_x;
	double		pos_y;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	double		side_dist_x;
	double		side_dist_y;
	int			side;
	double		perp_wall_dist;
}				t_dda;


/* ************************************************************************** */
/* Events Functions														      */
/* ************************************************************************** */

int				close_window(t_data *data);
int				handle_keypress(int keysym, t_data *data);
int				handle_keyrelease(int keysym, t_data *data);
void			process_input(t_data *data);

/* ************************************************************************** */
/* Parsing functions														  */
/* ************************************************************************** */

int				validate_file(const char *filename);
int				read_map_file(const char *filename, char ***lines, int *count);
int				parse_cub_file(const char *filename, t_map *map);
int				pad_map_grid(t_map *map);
int				extract_player_data(t_map *map);
int				check_map_enclosed(t_map *map);
void			free_map(t_map *map);

/* ************************************************************************** */
/* Initialization functions													  */
/* ************************************************************************** */

int				init_image(t_data *data);
int				init_mlx(t_data *data);

/* ************************************************************************** */
/* Render functions															  */
/* ************************************************************************** */

unsigned char	*get_pixel_ptr(t_data *data, int x, int y);
int				put_pixel(t_data *data, int x, int y, int color);
void			render_image(t_data *data);
void			render_floor_and_ceiling(t_data *data);
int				clamp_int(int value, int min, int max);
void			write_pixel_color(t_data *data, unsigned char *pixel,
					int color);
void			draw_wall_column(t_data *data, int x, t_dda *dda);
int				get_wall_color(t_dda *dda);
void			render_raycasting(t_data *data);
int				render_loop(void *param);
void			fill_row(t_data *data, int y, int color);
int				rgb_to_int(int rgb[3]);

/* ************************************************************************** */
/* Raycasting functions														  */
/* ************************************************************************** */

void			compute_ray_direction(t_data *data, int x, double *ray_dir_x,
					double *ray_dir_y);
void			init_dda_for_ray(t_data *data, int x, t_dda *dda);
double			compute_perp_wall_dist(t_dda *dda);
int				perform_dda(t_data *data, t_dda *dda);
double			get_dda_infinity(t_data *data);
double			compute_perp_wall_dist(t_dda *dda);
int				is_wall_cell(t_data *data, int x, int y);

/* ************************************************************************** */
/* texture_load functions													  */
/* ************************************************************************** */

int	load_one_texture(t_data *data, int index, char *path);
int	load_wall_texture(t_data *data);
int	load_all_textures(t_data *data);

/* ************************************************************************** */
/* Movement functions														  */
/* ************************************************************************** */

int				can_move_to(t_map *map, double x, double y);
void			move_player(t_map *map, int direction);
void			strafe_player(t_map *map, int direction);
void			rotate_player(t_map *map, double angle);
void			set_key_state(t_data *data, int keysym, int pressed);
void			process_input(t_data *data);
int				handle_keypress(int keysym, t_data *data);
int				handle_keyrelease(int keysym, t_data *data);
int				setup_hooks(t_data *data);


#endif