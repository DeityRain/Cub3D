/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 09:30:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/03 16:20:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** strip_line: Removes trailing newlines from duplicated string.
*/
char	*strip_line(const char *s)
{
	char	*dup;
	int		len;
	int		i;

	dup = ft_strdup(s);
	if (!dup)
		return (NULL);
	len = ft_strlen(dup);
	while (len > 0 && (dup[len - 1] == '\n' || dup[len - 1] == '\r'))
		dup[--len] = '\0';
	i = 0;
	while (dup[i])
	{
		if (dup[i] == ' ' || dup[i] == '\t')
			dup[i] = '1';
		i++;
	}
	return (dup);
}

/*
** is_valid_map_char: Checks if char is valid in map grid.
*/
int	is_valid_map_char(char ch)
{
	return (ch == '0' || ch == '1' || ch == ' ' || ch == '\t'
		|| ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W');
}

/*
** is_player_char: Checks if char is a player spawn marker.
*/
int	is_player_char(char ch)
{
	return (ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W');
}
