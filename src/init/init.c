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

/*
** init_mlx: Initializes MLX context and window.
*/
int	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		ft_putendl_fd("Error: failed to init MLX", 2);
		return (0);
	}
	return (1);
}

/*
** Initializes the game image.
*/
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
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
		data->img.img_ptr = NULL;
		return (0);
	}
	return (1);
}

/*
** setup_window: Creates window and attaches hooks.
*/
int	setup_window(t_data *data)
{
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!data->win_ptr)
	{
		ft_putendl_fd("Error: failed to create window", 2);
		return (0);
	}
	if (!setup_hooks(data))
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		return (0);
	}
	return (1);
}
