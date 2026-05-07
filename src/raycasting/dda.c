/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 10:02:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/07 13:44:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//DDA is for Digital Differential Analyzer

/*
** init_dda_distances: Sets delta distances for one grid step in X and Y.
*/
static void	init_dda_distances(t_data *data, t_dda *dda)
{
	double	infinity;

	infinity = get_dda_infinity(data);
	if (dda->ray_dir_x == 0)
		dda->delta_dist_x = infinity;
	else
		dda->delta_dist_x = fabs(1.0 / dda->ray_dir_x);
	if (dda->ray_dir_y == 0)
		dda->delta_dist_y = infinity;
	else
		dda->delta_dist_y = fabs(1.0 / dda->ray_dir_y);
}

/*
** init_dda_x: Sets X direction step and first X side distance.
*/
static void	init_dda_x(t_dda *dda)
{
	if (dda->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (dda->pos_x - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - dda->pos_x) * dda->delta_dist_x;
	}
}

/*
** init_dda_y: Sets Y direction step and first Y side distance.
*/
static void	init_dda_y(t_dda *dda)
{
	if (dda->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (dda->pos_y - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - dda->pos_y) * dda->delta_dist_y;
	}
}

/*
** init_dda_for_ray: Initializes DDA values for one screen-column ray.
*/
void	init_dda_for_ray(t_data *data, int x, t_dda *dda)
{
	dda->pos_x = data->map.player_x;
	dda->pos_y = data->map.player_y;
	compute_ray_direction(data, x, &dda->ray_dir_x, &dda->ray_dir_y);
	dda->map_x = (int)dda->pos_x;
	dda->map_y = (int)dda->pos_y;
	init_dda_distances(data, dda);
	init_dda_x(dda);
	init_dda_y(dda);
	dda->side = 0;
	dda->perp_wall_dist = 0.0;
}

/*
** perform_dda: Walks through the grid until the ray hits a wall.
*/
int	perform_dda(t_data *data, t_dda *dda)
{
	if (!data || !dda)
		return (0);
	while (1)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (is_wall_cell(data, dda->map_x, dda->map_y))
			break ;
	}
	compute_perp_wall_dist(dda);
	return (1);
}
