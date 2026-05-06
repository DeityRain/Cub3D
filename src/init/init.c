/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 13:25:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/06 14:10:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_image(t_data *data)
{
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img.img_ptr)
	{
		fprintf(stderr, "Error: Failed to create new image\n");
		return (0);
	}
	data->img.addr = mlx_get_data_addr(data->img.img_ptr,
			&data->img.bits_per_pixel, &data->img.line_length,
			&data->img.endian);
	if (!data->img.addr)
	{
		fprintf(stderr, "Error: Failed to get image data address\n");
		return (0);
	}
	return (1);
}
