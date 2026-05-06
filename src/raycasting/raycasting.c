/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                      :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:14:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/06 16:20:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Computes ray direction for a given screen column x.
*/
void	compute_ray_direction(t_data *data, int x, double *ray_dir_x,
		double *ray_dir_y)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0;
	*ray_dir_x = data->map.dir_x + data->map.plane_x * camera_x;
	*ray_dir_y = data->map.dir_y + data->map.plane_y * camera_x;
}
