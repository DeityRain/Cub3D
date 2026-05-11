/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 12:07:06 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/07 12:07:07 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** draw a vertical wall column (col[0]=start, col[1]=end).
*/
static void	draw_solid_column(t_data *data, int x, t_dda *dda, int col[3])
{
	int	y;
	int	color;

	color = get_wall_color(dda);
	y = col[0];
	while (y <= col[1])
	{
		put_pixel(data, x, y, color);
		y++;
	}
}

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
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				col[3];

	if (!data || !dda || dda->perp_wall_dist <= 0.0)
		return ;
	line_height = (int)(WIN_HEIGHT / dda->perp_wall_dist);
	if (line_height <= 0)
		line_height = 1;
	draw_start = (WIN_HEIGHT - line_height) / 2 + data->pitch_offset;
	draw_end = (WIN_HEIGHT + line_height) / 2 + data->pitch_offset;
	draw_start = clamp_int(draw_start, 0, WIN_HEIGHT - 1);
	draw_end = clamp_int(draw_end, 0, WIN_HEIGHT - 1);
	col[0] = draw_start;
	col[1] = draw_end;
	col[2] = line_height;
	if (!data->tex[0].img_ptr && !data->tex[1].img_ptr
		&& !data->tex[2].img_ptr && !data->tex[3].img_ptr)
	{
		draw_solid_column(data, x, dda, col);
		return ;
	}
	if (!render_draw_textured_column(data, x, dda, col))
		draw_solid_column(data, x, dda, col);
}

/*
** write_pixel_color: Writes color bytes to pixel memory using the image endian.
*/
void	write_pixel_color(t_data *data, unsigned char *pixel, int color)
{
	int				bytes_per_pixel;
	unsigned int	col;
	int				i;
	int				idx;

	bytes_per_pixel = data->img.bits_per_pixel / 8;
	col = mlx_get_color_value(data->mlx_ptr, color);
	i = 0;
	while (i < bytes_per_pixel)
	{
		idx = i;
		if (data->img.endian != 0)
			idx = bytes_per_pixel - 1 - i;
		pixel[idx] = (col >> (8 * i)) & 0xFF;
		i++;
	}
}
