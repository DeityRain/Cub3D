/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 17:00:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/10 17:00:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** bgr_order: extract RGB from BGR byte order
*/
static int	bgr_order(unsigned char *p)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	b = p[0];
	g = p[1];
	r = p[2];
	return ((r << 16) | (g << 8) | b);
}

/*
** rgb_order: extract RGB from RGB byte order
*/
static int	rgb_order(unsigned char *p)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = p[0];
	g = p[1];
	b = p[2];
	return ((r << 16) | (g << 8) | b);
}

/*
** sample_tex: sample a pixel from a loaded texture and return 0xRRGGBB
*/
int	sample_tex(t_texture *tex, int tx, int ty)
{
	unsigned char	*p;
	int				t_bpp;

	if (!tex || !tex->addr || tx < 0 || ty < 0 || tx >= tex->width
		|| ty >= tex->height)
		return (0);
	t_bpp = tex->bits_per_pixel / 8;
	p = (unsigned char *)tex->addr + ty * tex->line_length + tx * t_bpp;
	if (t_bpp >= 3)
	{
		if (tex->endian == 0)
			return (bgr_order(p));
		else
			return (rgb_order(p));
	}
	return (0);
}
