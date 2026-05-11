/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_capture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 15:05:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/11 15:05:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_capture(t_data *data)
{
	if (!data || !data->mlx_ptr || !data->win_ptr)
		return (0);
	data->mouse_captured = 1;
	data->mouse_initialized = 0;
	mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
	mlx_mouse_move(data->mlx_ptr, data->win_ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (1);
}

void	mouse_release(t_data *data)
{
	if (!data || !data->mlx_ptr)
		return ;
	data->mouse_captured = 0;
	if (data->win_ptr)
		mlx_mouse_show(data->mlx_ptr, data->win_ptr);
}
