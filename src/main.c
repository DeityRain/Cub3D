/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 11:40:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/04 16:10:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** close_window: Cleans up resources and exits program.
*/
int	close_window(t_data *data)
{
	ft_putendl_fd("Closing game...", 1);
	if (data->win_ptr && data->mlx_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		free(data->mlx_ptr);
	free_map(&data->map);
	exit(0);
	return (0);
}

/*
** handle_keypress: Processes keyboard input events.
*/
int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == ESC_KEY)
		close_window(data);
	return (0);
}

/*
** init_mlx: Initializes MLX context and window.
*/
static int	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		ft_putendl_fd("Error: failed to init MLX", 2);
		return (0);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"cub3D");
	if (!data->win_ptr)
	{
		ft_putendl_fd("Error: failed to create window", 2);
		return (0);
	}
	return (1);
}

/*
** setup_hooks: Attaches keyboard and close event handlers.
*/
static int	setup_hooks(t_data *data)
{
	mlx_key_hook(data->win_ptr, handle_keypress, data);
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	return (1);
}

/*
** main: Entry point - parses map file and starts game loop.
*/
int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		ft_putendl_fd("Usage: ./cub3D <map.cub>", 2);
		return (1);
	}
	if (!validate_file(av[1]))
		return (1);
	if (!parse_cub_file(av[1], &data.map))
		return (1);
	if (!init_mlx(&data))
		return (free_map(&data.map), 1);
	if (!init_image(&data))
	{
		mlx_destroy_window(data.mlx_ptr, data.win_ptr);
		free(data.mlx_ptr);
		free_map(&data.map);
		return (1);
	}
	if (!setup_hooks(&data))
	{
		mlx_destroy_window(data.mlx_ptr, data.win_ptr);
		free(data.mlx_ptr);
		free_map(&data.map);
		return (1);
	}
	mlx_loop_hook(data.mlx_ptr, render_loop, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
