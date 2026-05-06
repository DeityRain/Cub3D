/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                             :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 14:35:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/06 14:55:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	render_image(t_data *data)
{
	if (!data || !data->mlx_ptr || !data->win_ptr || !data->img.img_ptr)
		return ;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0,
		0);
}

int render_loop(void *param)
{
    t_data  *data;
    int     x;
    int     y;
    int     ceil_col;
    int     floor_col;

    data = (t_data *) param;
    ceil_col = (data->map.ceiling_rgb[0] << 16) | (data->map.ceiling_rgb[1] << 8) | data->map.ceiling_rgb[2];
    floor_col = (data->map.floor_rgb[0] << 16) | (data->map.floor_rgb[1] << 8) | data->map.floor_rgb[2];

    for(y = 0; y < (WIN_HEIGHT / 2); ++y)
    {
        for(x = 0; x < WIN_WIDTH; ++x)
            put_pixel(data, x, y, ceil_col);
    }
    for(y = (WIN_HEIGHT / 2); y < WIN_HEIGHT; ++y)
    {
        for(x = 0; x < WIN_WIDTH; ++x)
            put_pixel(data, x, y, floor_col);
    }
    render_image(data);
    return (0);
}
