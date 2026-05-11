/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 14:40:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/11 14:40:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_images(t_data *data)
{
	int	i;

	if (!data || !data->mlx_ptr)
		return ;
	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	data->img.img_ptr = NULL;
	i = 0;
	while (i < 4)
	{
		if (data->tex[i].img_ptr)
			mlx_destroy_image(data->mlx_ptr, data->tex[i].img_ptr);
		data->tex[i].img_ptr = NULL;
		i++;
	}
	if (data->floor_tex.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->floor_tex.img_ptr);
	data->floor_tex.img_ptr = NULL;
	if (data->ceil_tex.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->ceil_tex.img_ptr);
	data->ceil_tex.img_ptr = NULL;
}

void	destroy_game(t_data *data)
{
	if (!data)
		return ;
	destroy_images(data);
	if (data->win_ptr && data->mlx_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	data->mlx_ptr = NULL;
	free_map(&data->map);
}
