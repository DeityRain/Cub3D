/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 14:35:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/06 14:55:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** clamp_int: Keeps a value inside [min, max].
*/
int	clamp_int(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

/*
** render_raycasting: Casts one ray per screen column.
** 1e30 is a very large number i use it for representing the infinity
*/
void	render_raycasting(t_data *data)
{
	int		x;
	t_dda	dda;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_dda_for_ray(data, x, &dda);
		perform_dda(data, &dda);
		draw_wall_column(data, x, &dda);
		x++;
	}
}

/*
** render_loop: Main render callback called every frame by MLX.
*/
int	render_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	process_input(data);
	render_floor_and_ceiling(data);
	render_raycasting(data);
	render_image(data);
	return (0);
}
