/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 12:07:06 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/07 12:07:07 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Sets pixel at (x,y) in image buffer to given color.
*/
int	put_pixel(t_data *data, int x, int y, int color)
{
	unsigned char	*pixel;

	if (!data || !data->img.addr)
		return (0);
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return (0);
	pixel = get_pixel_ptr(data, x, y);
	write_pixel_color(data, pixel, color);
	return (1);
}

/*
** draw_wall_column: Draws one vertical wall slice on screen.
*/
void	draw_wall_column(t_data *data, int x, t_dda *dda)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	y;
	int	color;

	if (!data || !dda || dda->perp_wall_dist <= 0.0)
		return ;
	line_height = (int)(WIN_HEIGHT / dda->perp_wall_dist);
	if (line_height <= 0)
		line_height = 1;
	draw_start = (WIN_HEIGHT - line_height) / 2;
	draw_end = (WIN_HEIGHT + line_height) / 2;
	draw_start = clamp_int(draw_start, 0, WIN_HEIGHT - 1);
	draw_end = clamp_int(draw_end, 0, WIN_HEIGHT - 1);
	color = get_wall_color(dda);
	y = draw_start;
	while (y <= draw_end)
	{
		put_pixel(data, x, y, color);
		y++;
	}
}

/*
** write_pixel_color: Writes color bytes to pixel memory using the image endian.
*/
void	write_pixel_color(t_data *data, unsigned char *pixel, int color)
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
