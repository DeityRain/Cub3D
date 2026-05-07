/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:10:56 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/07 14:10:57 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** get_dda_infinity: Returns a large safe distance based on the current map.
** It is large enough to be treated like infinity for DDA stepping but stays
** finite and proportional to the actual map size.
*/
double	get_dda_infinity(t_data *data)
{
	double	max_dim;

	if (!data)
		return (INFINITY);
	max_dim = hypot((double)data->map.width, (double)data->map.height);
	return (max_dim + 10.0);
}

/*
** compute_perp_wall_dist: Returns the perpendicular distance to the wall hit.
** This uses the side that the DDA hit, so the caller must set dda->side
** during the DDA stepping phase.
*/
double	compute_perp_wall_dist(t_dda *dda)
{
	if (!dda)
		return (INFINITY);
	if (dda->side == 0)
		dda->perp_wall_dist = dda->side_dist_x - dda->delta_dist_x;
	else
		dda->perp_wall_dist = dda->side_dist_y - dda->delta_dist_y;
	return (dda->perp_wall_dist);
}

/*
** is_wall_cell: Returns 1 when the current grid cell is a wall.
** The map is padded, so going outside the original play area should still hit
** the border walls, but we keep the bounds check for safety.
*/
int	is_wall_cell(t_data *data, int x, int y)
{
	if (!data || !data->map.grid)
		return (1);
	if (x < 0 || y < 0 || x >= data->map.width || y >= data->map.height)
		return (1);
	return (data->map.grid[y][x] == '1');
}
