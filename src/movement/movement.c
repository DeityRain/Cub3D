/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 12:58:31 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/07 12:58:33 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** can_move_to: Returns 1 if the target grid position is not a wall.
*/
int	can_move_to(t_map *map, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || map_x >= map->width || map_y >= map->height)
		return (0);
	return (map->grid[map_y][map_x] != '1');
}

/*
** move_player: Moves forward or backward along the direction vector.
*/
void	move_player(t_map *map, int direction)
{
	double	next_x;
	double	next_y;

	next_x = map->player_x + map->dir_x * MOVE_SPEED * direction;
	next_y = map->player_y + map->dir_y * MOVE_SPEED * direction;
	if (can_move_to(map, next_x, map->player_y))
		map->player_x = next_x;
	if (can_move_to(map, map->player_x, next_y))
		map->player_y = next_y;
}

/*
** strafe_player: Moves left or right along the camera plane.
*/
void	strafe_player(t_map *map, int direction)
{
	double	next_x;
	double	next_y;

	next_x = map->player_x + map->plane_x * MOVE_SPEED * direction;
	next_y = map->player_y + map->plane_y * MOVE_SPEED * direction;
	if (can_move_to(map, next_x, map->player_y))
		map->player_x = next_x;
	if (can_move_to(map, map->player_x, next_y))
		map->player_y = next_y;
}

/*
** rotate_player: Rotates the view direction and camera plane.
*/
void	rotate_player(t_map *map, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = map->dir_x;
	old_plane_x = map->plane_x;
	map->dir_x = map->dir_x * cos(angle) - map->dir_y * sin(angle);
	map->dir_y = old_dir_x * sin(angle) + map->dir_y * cos(angle);
	map->plane_x = map->plane_x * cos(angle) - map->plane_y * sin(angle);
	map->plane_y = old_plane_x * sin(angle) + map->plane_y * cos(angle);
}
