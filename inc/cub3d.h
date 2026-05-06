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

/* ************************************************************************** */
/* Structures																  */
/* ************************************************************************** */

typedef struct s_map
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_texture;
	int			floor_rgb[3];
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

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_map		map;
}				t_data;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

/* ************************************************************************** */
/* Events Functions														      */
/* ************************************************************************** */

int				close_window(t_data *data);
int				handle_keypress(int keysym, t_data *data);

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
void			write_pixel_color(t_data *data, unsigned char *pixel,
					int color);
void			render_raycasting(t_data *data);
int				render_loop(void *param);
void			fill_row(t_data *data, int y, int color);
int				rgb_to_int(int rgb[3]);

/* ************************************************************************** */
/* Raycasting functions														  */
/* ************************************************************************** */

void			compute_ray_direction(t_data *data, int x, double *ray_dir_x,
					double *ray_dir_y);

#endif