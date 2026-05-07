/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_render.c                                      :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:28:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/06 15:39:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Calculates pointer to pixel data for (x,y) in image buffer.
*/
unsigned char	*get_pixel_ptr(t_data *data, int x, int y)
{
	int	bytes_per_pixel;
	int	offset;

	bytes_per_pixel = data->img.bits_per_pixel / 8;
	offset = y * data->img.line_length + x * bytes_per_pixel;
	return ((unsigned char *)data->img.addr + offset);
}

/*
** Writes a horizontal row of pixels with the given color.
*/
void	fill_row(t_data *data, int y, int color)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		put_pixel(data, x, y, color);
		x++;
	}
}

/*
** get_wall_color: Returns a simple wall color and darkens Y-side hits.
*/
int	get_wall_color(t_dda *dda)
{
	int	color;

	color = 0x777777;
	if (dda && dda->side == 1)
		color = 0x555555;
	return (color);
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
** rgb_to_int: Converts an RGB array into a single 0xRRGGBB color value.
*/
int	rgb_to_int(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
