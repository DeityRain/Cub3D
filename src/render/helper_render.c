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
** rgb_to_int: Converts an RGB array into a single 0xRRGGBB color value.
*/
int	rgb_to_int(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
