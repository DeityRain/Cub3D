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

static void	copy_tex_pixel_to_screen(t_data *data, int x, int y,
		t_texture *tex, int tx, int ty)
{
	unsigned char	*s_pixel;
	unsigned char	*t_pixel;
	int		s_bpp;
	int		t_bpp;

	if (!data || !tex || !tex->addr)
		return ;
	s_bpp = data->img.bits_per_pixel / 8;
	t_bpp = tex->bits_per_pixel / 8;
	if (tx < 0 || tx >= tex->width || ty < 0 || ty >= tex->height)
		return ;
	s_pixel = get_pixel_ptr(data, x, y);
	t_pixel = (unsigned char *)tex->addr + ty * tex->line_length + tx * t_bpp;
	if (s_bpp == t_bpp)
	{
		memcpy(s_pixel, t_pixel, s_bpp);
	}
	else if (t_bpp >= 3)
	{
		unsigned char r, g, b;
		if (tex->endian == 0)
		{
			b = t_pixel[0];
			g = t_pixel[1];
			r = t_pixel[2];
		}
		else
		{
			r = t_pixel[0];
			g = t_pixel[1];
			b = t_pixel[2];
		}
		put_pixel(data, x, y, (r << 16) | (g << 8) | b);
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
	draw_start = (WIN_HEIGHT - line_height) / 2 + data->pitch_offset;
	draw_end = (WIN_HEIGHT + line_height) / 2 + data->pitch_offset;
	draw_start = clamp_int(draw_start, 0, WIN_HEIGHT - 1);
	draw_end = clamp_int(draw_end, 0, WIN_HEIGHT - 1);
	/* textured walls */
	if (!data->tex[0].img_ptr && !data->tex[1].img_ptr && !data->tex[2].img_ptr && !data->tex[3].img_ptr)
	{
		color = get_wall_color(dda);
		y = draw_start;
		while (y <= draw_end)
		{
			put_pixel(data, x, y, color);
			y++;
		}
		return ;
	}

	/* choose texture index based on hit side and ray direction */
	int tex_idx;
	double wall_x;
	if (dda->side == 0)
	{
		/* vertical wall (x-side) */
		if (dda->ray_dir_x > 0)
			tex_idx = 2; /* WE */
		else
			tex_idx = 3; /* EA */
		wall_x = dda->pos_y + dda->perp_wall_dist * dda->ray_dir_y;
	}
	else
	{
		/* horizontal wall (y-side) */
		if (dda->ray_dir_y > 0)
			tex_idx = 1; /* SO */
		else
			tex_idx = 0; /* NO */
		wall_x = dda->pos_x + dda->perp_wall_dist * dda->ray_dir_x;
	}
	wall_x -= floor(wall_x);

	t_texture *tex = &data->tex[tex_idx];
	if (!tex->img_ptr || tex->width <= 0 || tex->height <= 0)
	{
		color = get_wall_color(dda);
		y = draw_start;
		while (y <= draw_end)
		{
			put_pixel(data, x, y, color);
			y++;
		}
		return ;
	}

	int tex_x = (int)(wall_x * (double)tex->width);
	if (dda->side == 0 && dda->ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (dda->side == 1 && dda->ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;

	double center = WIN_HEIGHT / 2.0 + data->pitch_offset;
	double step = 1.0 * tex->height / (double)line_height;
	double tex_pos = (draw_start - center + (line_height / 2.0)) * step;

	y = draw_start;
	while (y <= draw_end)
	{
		int tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		copy_tex_pixel_to_screen(data, x, y, tex, tex_x, tex_y);
		tex_pos += step;
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
