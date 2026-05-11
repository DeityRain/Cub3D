/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 00:00:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/11 00:00:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_wall_tex_idx(t_dda *dda)
{
	if (dda->side == 0)
	{
		if (dda->ray_dir_x > 0)
			return (2);
		return (3);
	}
	if (dda->ray_dir_y > 0)
		return (1);
	return (0);
}

static double	calc_wall_x(t_dda *dda)
{
	double	wall_x;

	if (dda->side == 0)
		wall_x = dda->pos_y + dda->perp_wall_dist * dda->ray_dir_y;
	else
		wall_x = dda->pos_x + dda->perp_wall_dist * dda->ray_dir_x;
	return (wall_x);
}

static int	calc_tex_x(t_dda *dda, t_texture *tex, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)tex->width);
	if ((dda->side == 0 && dda->ray_dir_x > 0)
		|| (dda->side == 1 && dda->ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	return (clamp_int(tex_x, 0, tex->width - 1));
}

static void	draw_tex_loop(t_data *data, int x, t_texture *tex, t_texloop *l)
{
	int	tex_y;

	while (l->y <= l->end)
	{
		tex_y = clamp_int((int)l->tex_pos, 0, tex->height - 1);
		put_pixel(data, x, l->y, sample_tex(tex, l->tex_x, tex_y));
		l->tex_pos += l->step;
		l->y++;
	}
}

/*
** render_draw_textured_column: draw a textured wall column (col[0]=start,
** col[1]=end, col[2]=line_height).
*/
int	render_draw_textured_column(t_data *data, int x, t_dda *dda, int col[3])
{
	int			tex_idx;
	double		wall_x;
	t_texture	*tex;
	int			tex_x;
	t_texloop	l;

	tex_idx = get_wall_tex_idx(dda);
	wall_x = calc_wall_x(dda);
	tex = &data->tex[tex_idx];
	if (!tex->img_ptr || tex->width <= 0 || tex->height <= 0)
		return (0);
	wall_x -= floor(wall_x);
	tex_x = calc_tex_x(dda, tex, wall_x);
	l.y = col[0];
	l.end = col[1];
	l.tex_x = tex_x;
	l.step = 1.0 * tex->height / (double)col[2];
	l.tex_pos = (col[0] - (WIN_HEIGHT / 2.0 + data->pitch_offset)
			+ (col[2] / 2.0)) * l.step;
	draw_tex_loop(data, x, tex, &l);
	return (1);
}
