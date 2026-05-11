/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 17:32:46 by deityrain         #+#    #+#             */
/*   Updated: 2026/05/10 17:33:40 by deityrain        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Sets mouse state when mouse is moved.
** Clamps mouse position to stay within window bounds.
*/
void	handle_mouse_delta(t_data *data, int delta_x, int delta_y)
{
	double	angle;

	if (delta_x != 0)
	{
		angle = delta_x * MOUSE_ROT_SPEED;
		rotate_player(&data->map, angle);
	}
	if (delta_y != 0)
		data->pitch_offset = clamp_int(data->pitch_offset - delta_y
				* MOUSE_PITCH_SPEED, -WIN_HEIGHT / 2, WIN_HEIGHT / 2);
	mlx_mouse_move(data->mlx_ptr, data->win_ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

/*
** Clears key state when a key is released.
*/
int	handle_keyrelease(int keysym, t_data *data)
{
	if (keysym == LCTRL_KEY)
	{
		data->mouse_captured = 1;
		data->mouse_initialized = 0;
		mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
		mlx_mouse_move(data->mlx_ptr, data->win_ptr, WIN_WIDTH / 2, WIN_HEIGHT
			/ 2);
	}
	set_key_state(data, keysym, 0);
	return (0);
}
