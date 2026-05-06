/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 14:35:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/06 14:55:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** write_pixel_color: Writes color bytes to pixel memory using the image endian.
*/
static void	write_pixel_color(t_data *data, unsigned char *pixel, int color)
{
	int				bytes_per_pixel;
	unsigned int	col;
	int				i;

	bytes_per_pixel = data->img.bits_per_pixel / 8;
	col = mlx_get_color_value(data->mlx_ptr, color);
	i = 0;
	if (data->img.endian == 0)
	{
		while (i < bytes_per_pixel)
		{
			pixel[i] = (col >> (8 * i)) & 0xFF;
			i++;
		}
	}
	else
	{
		while (i < bytes_per_pixel)
		{
			pixel[bytes_per_pixel - 1 - i] = (col >> (8 * i)) & 0xFF;
			i++;
		}
	}
}

/*
** render_image: Pushes the current image buffer to the MLX window.
*/
void	render_image(t_data *data)
{
	if (!data || !data->mlx_ptr || !data->win_ptr || !data->img.img_ptr)
		return ;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0,
		0);
}

/*
** render_floor_and_ceiling: Fills the top half and bottom half of the screen.
*/
void	render_floor_and_ceiling(t_data *data)
{
	int	x;
	int	y;
	int	ceil_col;
	int	floor_col;

	if (!data || !data->mlx_ptr || !data->win_ptr || !data->img.img_ptr)
		return ;
	ceil_col = rgb_to_int(data->map.ceil_rgb);
	floor_col = rgb_to_int(data->map.floor_rgb);
	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		fill_row(data, y, ceil_col);
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		fill_row(data, y, floor_col);
		y++;
	}
}

/*
** render_raycasting: Casts one ray per screen column.
*/
void	render_raycasting(t_data *data)
{
	int		x;
	double	ray_dir_x;
	double	ray_dir_y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		compute_ray_direction(data, x, &ray_dir_x, &ray_dir_y);
		x++;
	}
}

/*
** render_loop: Main render callback called every frame by MLX.
*/
int	render_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	render_floor_and_ceiling(data);
	render_raycasting(data);
	render_image(data);
	return (0);
}
