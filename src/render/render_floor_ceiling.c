/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 17:00:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/10 17:00:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** render_solid_floor_ceiling: Fills floor/ceiling with solid colors.
*/
static void	render_solid_floor_ceiling(t_data *data, int center)
{
	int	y;
	int	ceil_col;
	int	floor_col;

	ceil_col = rgb_to_int(data->map.ceil_rgb);
	floor_col = rgb_to_int(data->map.floor_rgb);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y < center)
			fill_row(data, y, ceil_col);
		else
			fill_row(data, y, floor_col);
		y++;
	}
}

/*
** render_floor_and_ceiling: Fills the top half and bottom half of the screen.
*/
void	render_floor_and_ceiling(t_data *data)
{
	int	center;

	if (!data || !data->mlx_ptr || !data->win_ptr || !data->img.img_ptr)
		return ;
	center = WIN_HEIGHT / 2 + data->pitch_offset;
	center = clamp_int(center, 0, WIN_HEIGHT);
	if (!data->floor_tex.img_ptr && !data->ceil_tex.img_ptr)
		render_solid_floor_ceiling(data, center);
	else
		render_floor_ceiling_textured(data, center);
}
