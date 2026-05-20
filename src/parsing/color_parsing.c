/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:25:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/05/02 14:10:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** free_split: Frees array of strings from ft_split.
*/
static void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

/*
** validate_rgb_values: Validates and assigns RGB values from parts array.
*/
static int	validate_rgb_values(char **parts, int out[3])
{
	int	i;
	int	val;

	i = 0;
	while (i < 3)
	{
		val = ft_atoi(parts[i]);
		if (val < 0 || val > 255)
			return (0);
		out[i] = val;
		i++;
	}
	return (1);
}

static int	is_strict_rgb_format(const char *s)
{
	int	comma_count;
	int	i;

	comma_count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == ',')
			comma_count++;
		else if (!ft_isdigit(s[i]) && s[i] != ' ' && s[i] != '\t'
			&& s[i] != '\n' && s[i] != '\r')
			return (0);
		i++;
	}
	return (comma_count == 2);
}

/*
** print_color_error
*/
static int	print_color_error(char *trimmed)
{
	ft_putendl_fd("Error: invalid strict RGB format", 2);
	free(trimmed);
	return (-1);
}

/*
** parse_color: Parses "R,G,B" format into 3 integers [0-255].
*/
int	parse_color(const char *s, int out[3])
{
	char	*trimmed;
	char	**parts;
	int		i;

	if (!s)
		return (0);
	trimmed = ft_strtrim(s, " \t");
	if (!trimmed)
		return (0);
	if (!is_strict_rgb_format(trimmed))
		return (print_color_error(trimmed));
	parts = ft_split(trimmed, ',');
	free(trimmed);
	if (!parts)
		return (0);
	i = 0;
	while (parts[i])
		i++;
	if (i != 3)
		return (free_split(parts), 0);
	if (!validate_rgb_values(parts, out))
		return (free_split(parts), 0);
	free_split(parts);
	return (1);
}
