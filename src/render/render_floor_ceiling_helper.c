/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_ceiling_helper.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 00:00:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/11 00:00:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fc_calc_row(t_fc_state *state, t_fc_row *row)
{
	int	p;

	p = state->center - row->y;
	if (p < 0)
		p = -p;
	if (p == 0)
		p = 1;
	row->row_dist = (0.5 * WIN_HEIGHT) / (double)p;
	row->step_x = row->row_dist * (state->rays.x1 - state->rays.x0)
		/ (double)WIN_WIDTH;
	row->step_y = row->row_dist * (state->rays.y1 - state->rays.y0)
		/ (double)WIN_WIDTH;
	row->tex_x = state->data->map.player_x + row->row_dist * state->rays.x0;
	row->tex_y = state->data->map.player_y + row->row_dist * state->rays.y0;
	if (row->y < state->center)
		row->tex = &state->data->ceil_tex;
	else
		row->tex = &state->data->floor_tex;
}

static void	fc_draw_row_pixels(t_fc_state *state, t_fc_row *row)
{
	int	x;
	int	cell_x;
	int	cell_y;
	int	tx;
	int	ty;

	x = 0;
	while (x < WIN_WIDTH)
	{
		cell_x = (int)row->tex_x;
		cell_y = (int)row->tex_y;
		tx = (int)(row->tex->width * (row->tex_x - cell_x));
		ty = (int)(row->tex->height * (row->tex_y - cell_y));
		put_pixel(state->data, x, row->y, sample_tex(row->tex, tx, ty));
		row->tex_x += row->step_x;
		row->tex_y += row->step_y;
		x++;
	}
}

static void	fc_draw_row(t_fc_state *state, int y)
{
	t_fc_row	row;

	row.y = y;
	fc_calc_row(state, &row);
	fc_draw_row_pixels(state, &row);
}

static void	fc_init_state(t_fc_state *state, t_data *data, int center)
{
	state->data = data;
	state->center = center;
	state->ceil_col = rgb_to_int(data->map.ceil_rgb);
	state->floor_col = rgb_to_int(data->map.floor_rgb);
	state->rays.x0 = data->map.dir_x - data->map.plane_x;
	state->rays.y0 = data->map.dir_y - data->map.plane_y;
	state->rays.x1 = data->map.dir_x + data->map.plane_x;
	state->rays.y1 = data->map.dir_y + data->map.plane_y;
}

void	render_floor_ceiling_textured(t_data *data, int center)
{
	t_fc_state	state;
	int			y;

	fc_init_state(&state, data, center);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		if ((y < center && !data->ceil_tex.img_ptr)
			|| (y >= center && !data->floor_tex.img_ptr))
		{
			if (y < center)
				fill_row(data, y, state.ceil_col);
			else
				fill_row(data, y, state.floor_col);
		}
		else
			fc_draw_row(&state, y);
		y++;
	}
}
