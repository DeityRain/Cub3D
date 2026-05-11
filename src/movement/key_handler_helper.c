/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 17:32:46 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/10 17:33:40 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_init_center(t_data *data)
{
	data->mouse_initialized = 1;
	mlx_mouse_move(data->mlx_ptr, data->win_ptr,
		WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (0);
}

void	mouse_clamp_pos(int pos[2], int x, int y)
{
	pos[0] = x;
	if (pos[0] < 0)
		pos[0] = 0;
	else if (pos[0] >= WIN_WIDTH)
		pos[0] = WIN_WIDTH - 1;
	pos[1] = y;
	if (pos[1] < 0)
		pos[1] = 0;
	else if (pos[1] >= WIN_HEIGHT)
		pos[1] = WIN_HEIGHT - 1;
}

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
	if (delta_x != 0 || delta_y != 0)
		mlx_mouse_move(data->mlx_ptr, data->win_ptr,
			WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

/*
** Clears key state when a key is released.
*/
int	handle_keyrelease(int keysym, t_data *data)
{
	if (keysym == LCTRL_KEY)
	{
		if (!mouse_capture(data))
			return (ft_putendl_fd("Error: failed to grab mouse pointer", 2), 0);
	}
	set_key_state(data, keysym, 0);
	return (0);
}
