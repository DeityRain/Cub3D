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
** verifications: Validates file, parses map, and initializes MLX/image.
*/
static int	verifications(t_data *data, char **av)
{
	if (!validate_file(av[1]))
		return (0);
	if (!parse_cub_file(av[1], &data->map))
		return (0);
	if (!init_mlx(data))
		return (free_map(&data->map), 0);
	if (!init_image(data))
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free(data->mlx_ptr);
		free_map(&data->map);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		ft_putendl_fd("Usage: ./cub3D <map.cub>", 2);
		return (1);
	}
	ft_bzero(&data, sizeof(t_data));
	if (!verifications(&data, av) || !load_all_textures(&data))
	{
		ft_putendl_fd("Error: failed to initialize game", 2);
		return (1);
	}
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT,"cub3D");
	if (!data.win_ptr)
	{
		ft_putendl_fd("Error: failed to create window", 2);
		return (0);
	}
	if (!setup_hooks(&data))
	{
		mlx_destroy_window(data.mlx_ptr, data.win_ptr);
		free(data.mlx_ptr);
		free_map(&data.map);
		return (0);
	}
	mlx_loop_hook(data.mlx_ptr, render_loop, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
