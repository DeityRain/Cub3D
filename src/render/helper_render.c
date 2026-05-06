/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_render.c                                      :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:28:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/06 15:39:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned char	*get_pixel_ptr(t_data *data, int x, int y)
{
	int	bytes_per_pixel;
	int	offset;

	bytes_per_pixel = data->img.bits_per_pixel / 8;
	offset = y * data->img.line_length + x * bytes_per_pixel;
	return ((unsigned char *)data->img.addr + offset);
}