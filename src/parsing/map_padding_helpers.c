/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_padding_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 17:00:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/10 17:00:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** free_partial_grid: Frees allocated rows in temporary padded grid.
*/
void	free_partial_grid(char **grid, int count)
{
	while (count > 0)
		free(grid[--count]);
	free(grid);
}
