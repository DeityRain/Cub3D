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
** clamp_int: Keeps a value inside [min, max].
*/
int	clamp_int(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

/* sample_tex: sample a pixel from a loaded texture and return 0xRRGGBB */
static int	sample_tex(t_texture *tex, int tx, int ty)
{
	unsigned char *p;
	unsigned char r = 0, g = 0, b = 0;
	int t_bpp;

	if (!tex || !tex->addr || tx < 0 || ty < 0 || tx >= tex->width || ty >= tex->height)
		return (0);
	t_bpp = tex->bits_per_pixel / 8;
	p = (unsigned char *)tex->addr + ty * tex->line_length + tx * t_bpp;
	if (t_bpp >= 3)
	{
		if (tex->endian == 0)
		{
			b = p[0];
			g = p[1];
			r = p[2];
		}
		else
		{
			r = p[0];
			g = p[1];
			b = p[2];
		}
	}
	return ((r << 16) | (g << 8) | b);
}

/*
** render_floor_and_ceiling: Fills the top half and bottom half of the screen.
*/
void	render_floor_and_ceiling(t_data *data)
{
	int	y;
	int	x;
	int	ceil_col;
	int	floor_col;
	t_texture	*ftex;
	t_texture	*ctex;
	int	center;

	if (!data || !data->mlx_ptr || !data->win_ptr || !data->img.img_ptr)
		return ;
	ceil_col = rgb_to_int(data->map.ceil_rgb);
	floor_col = rgb_to_int(data->map.floor_rgb);
	ftex = &data->floor_tex;
	ctex = &data->ceil_tex;
	center = WIN_HEIGHT / 2 + data->pitch_offset;
	center = clamp_int(center, 0, WIN_HEIGHT);

	if (!ftex->img_ptr && !ctex->img_ptr)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			if (y < center)
				fill_row(data, y, ceil_col);
			else
				fill_row(data, y, floor_col);
			y++;
		}
		return ;
	}

	{
		double rayDirX0 = data->map.dir_x - data->map.plane_x;
		double rayDirY0 = data->map.dir_y - data->map.plane_y;
		double rayDirX1 = data->map.dir_x + data->map.plane_x;
		double rayDirY1 = data->map.dir_y + data->map.plane_y;

		y = 0;
		while (y < WIN_HEIGHT)
		{
			if (y < center)
			{
				if (!ctex->img_ptr)
					fill_row(data, y, ceil_col);
				else
				{
					int p = center - y;
					if (p == 0)
						p = 1;
					double rowDistance = (0.5 * WIN_HEIGHT) / (double)p;
					double ceilStepX = rowDistance * (rayDirX1 - rayDirX0) / (double)WIN_WIDTH;
					double ceilStepY = rowDistance * (rayDirY1 - rayDirY0) / (double)WIN_WIDTH;
					double ceilX = data->map.player_x + rowDistance * rayDirX0;
					double ceilY = data->map.player_y + rowDistance * rayDirY0;
					x = 0;
					while (x < WIN_WIDTH)
					{
						int cellX = (int)ceilX;
						int cellY = (int)ceilY;
						int tx = (int)(ctex->width * (ceilX - cellX));
						int ty = (int)(ctex->height * (ceilY - cellY));
						put_pixel(data, x, y, sample_tex(ctex, tx, ty));
						ceilX += ceilStepX;
						ceilY += ceilStepY;
						x++;
					}
				}
			}
			else
			{
				if (!ftex->img_ptr)
					fill_row(data, y, floor_col);
				else
				{
					int p = y - center;
					if (p == 0)
						p = 1;
					double rowDistance = (0.5 * WIN_HEIGHT) / (double)p;
					double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / (double)WIN_WIDTH;
					double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / (double)WIN_WIDTH;
					double floorX = data->map.player_x + rowDistance * rayDirX0;
					double floorY = data->map.player_y + rowDistance * rayDirY0;
					x = 0;
					while (x < WIN_WIDTH)
					{
						int cellX = (int)floorX;
						int cellY = (int)floorY;
						int tx = (int)(ftex->width * (floorX - cellX));
						int ty = (int)(ftex->height * (floorY - cellY));
						put_pixel(data, x, y, sample_tex(ftex, tx, ty));
						floorX += floorStepX;
						floorY += floorStepY;
						x++;
					}
				}
			}
			y++;
		}
	}
}

/*
** render_raycasting: Casts one ray per screen column.
** 1e30 is a very large number i use it for representing the infinity
*/
void	render_raycasting(t_data *data)
{
	int		x;
	t_dda	dda;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_dda_for_ray(data, x, &dda);
		perform_dda(data, &dda);
		draw_wall_column(data, x, &dda);
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
	process_input(data);
	render_floor_and_ceiling(data);
	render_raycasting(data);
	render_image(data);
	return (0);
}
