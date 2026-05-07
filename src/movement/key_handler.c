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
}

/*
** process_input: Applies movement and rotation while keys are held.
*/
void	process_input(t_data *data)
{

	if (data->key_up || data->key_w)
		move_player(&data->map, 1);
	if (data->key_down || data->key_s)
		move_player(&data->map, -1);
	if (data->key_a)
		rotate_player(&data->map, -ROT_SPEED);
	if (data->key_d)
		rotate_player(&data->map, ROT_SPEED);
	if (data->key_left)
		rotate_player(&data->map, -ROT_SPEED);
	if (data->key_right)
		rotate_player(&data->map, ROT_SPEED);
}

/*
** handle_keypress: Sets key state when a key is pressed.
*/
int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == ESC_KEY)
		close_window(data);
	set_key_state(data, keysym, 1);
	return (0);
}

/*
** handle_keyrelease: Clears key state when a key is released.
*/
int	handle_keyrelease(int keysym, t_data *data)
{
	set_key_state(data, keysym, 0);
	return (0);
}

/*
** setup_hooks: Attaches keyboard and close event handlers.
*/
int	setup_hooks(t_data *data)
{
	mlx_hook(data->win_ptr, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, handle_keyrelease, data);
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	return (1);
}
