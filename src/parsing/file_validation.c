/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 11:20:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/04/28 11:05:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** check_file_extension: Validates that filename ends with .cub
*/
static int	check_file_extension(const char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

/*
** validate_file: Checks .cub extension and file readability.
*/
int	validate_file(const char *filename)
{
	int	fd;

	if (!check_file_extension(filename))
	{
		ft_putendl_fd("Error: file must have .cub extension", 2);
		return (0);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Error: cannot open file", 2);
		return (0);
	}
	close(fd);
	return (1);
}
