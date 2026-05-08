/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:06:27 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/07 14:06:29 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** set_key_state: Tracks whether a key is currently pressed.
*/
void	set_key_state(t_data *data, int keysym, int pressed)
{
	if (keysym == W_KEY)
		data->key_w = pressed;
	else if (keysym == A_KEY)
		data->key_a = pressed;
	else if (keysym == S_KEY)
		data->key_s = pressed;
	else if (keysym == D_KEY)
		data->key_d = pressed;
	else if (keysym == UP_KEY)
		data->key_up = pressed;
	else if (keysym == DOWN_KEY)
		data->key_down = pressed;
	else if (keysym == LEFT_KEY)
		data->key_left = pressed;
	else if (keysym == RIGHT_KEY)
		data->key_right = pressed;
	else if (keysym == LCTRL_KEY)
		data->key_ctrl = pressed;
}

/*
** process_input: Applies movement and rotation while keys are held.
*/
void	process_input(t_data *data)
{

	if (data->key_w)
		move_player(&data->map, 1);
	if (data->key_s)
		move_player(&data->map, -1);
	if (data->key_a)
		strafe_player(&data->map, -1);
	if (data->key_d)
		strafe_player(&data->map, 1);
	if (data->key_up)
		data->pitch_offset = clamp_int(data->pitch_offset + PITCH_SPEED,
			-WIN_HEIGHT / 2, WIN_HEIGHT / 2);
	if (data->key_down)
		data->pitch_offset = clamp_int(data->pitch_offset - PITCH_SPEED,
			-WIN_HEIGHT / 2, WIN_HEIGHT / 2);
	if (data->key_left)
		rotate_player(&data->map, -ROT_SPEED);
	if (data->key_right)
		rotate_player(&data->map, ROT_SPEED);
}

/*
** Sets mouse state when mouse is moved.
*/
int	handle_mouse_move(int x, int y, t_data *data)
{
	int	delta_x;
	int	delta_y;

	(void)y;

	if (!data->mouse_captured)
		return (0);
	if (!data->mouse_initialized)
	{
		data->mouse_initialized = 1;
		return (0);
	}
	delta_x = x - WIN_WIDTH / 2;
	delta_y = y - WIN_HEIGHT / 2;
	if (delta_x != 0)
	{
		double angle = delta_x * MOUSE_ROT_SPEED;

		rotate_player(&data->map, angle);
	}
	if (delta_y != 0)
	{
		data->pitch_offset = clamp_int(data->pitch_offset - delta_y * MOUSE_PITCH_SPEED,
			-WIN_HEIGHT / 2, WIN_HEIGHT / 2);
	}
	mlx_mouse_move(data->mlx_ptr, data->win_ptr,
		WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (0);
}


/*
** Sets key state when a key is pressed.
*/
int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == ESC_KEY)
		close_window(data);
	if (keysym == LCTRL_KEY)
	{
		data->mouse_captured = 0;
		mlx_mouse_show(data->mlx_ptr, data->win_ptr);
	}
	set_key_state(data, keysym, 1);
	return (0);
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
		mlx_mouse_move(data->mlx_ptr, data->win_ptr,
			WIN_WIDTH / 2, WIN_HEIGHT / 2);
	}
	set_key_state(data, keysym, 0);
	return (0);
}

/*
** Attaches keyboard and close event handlers.
*/
int	setup_hooks(t_data *data)
{
	mlx_hook(data->win_ptr, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, handle_keyrelease, data);
	mlx_hook(data->win_ptr, 6, 1L << 6, handle_mouse_move, data);
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	data->mouse_captured = 1;
	mlx_mouse_move(data->mlx_ptr, data->win_ptr, WIN_WIDTH / 2,
		WIN_HEIGHT / 2);
	mlx_mouse_hide(data->mlx_ptr, data->win_ptr);

	return (1);
}
