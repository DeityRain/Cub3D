/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42luxembourg.lu> +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 09:42:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2026/04/28 10:15:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** expand_lines_buffer: Reallocates lines array when capacity is reached.
*/
static int	expand_lines_buffer(char ***arr, int *capacity, int n)
{
	int		newcap;
	char	**tmp;

	if (n < *capacity)
		return (1);
	newcap = *capacity * 2;
	tmp = realloc(*arr, sizeof(char *) * newcap);
	if (!tmp)
		return (0);
	*arr = tmp;
	*capacity = newcap;
	return (1);
}

/*
** free_lines_array: Frees all line strings and the lines array.
*/
void	free_lines_array(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(arr[i++]);
	free(arr);
}

/*
** read_and_buffer_lines: Reads lines from file and buffers them.
*/
static int	read_and_buffer_lines(int fd, char ***arr, int *cap, int *n)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!expand_lines_buffer(arr, cap, *n))
			return (free_lines_array(*arr, *n), free(line), close(fd), 0);
		(*arr)[(*n)++] = line;
	}
	return (1);
}

/*
** read_map_file: Reads all lines from file into a dynamic array.
*/
int	read_map_file(const char *filename, char ***lines, int *count)
{
	int		fd;
	char	**arr;
	int		capacity;
	int		n;

	if (!filename || !lines || !count)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	capacity = 16;
	arr = malloc(sizeof(char *) * capacity);
	if (!arr)
		return (close(fd), 0);
	n = 0;
	if (!read_and_buffer_lines(fd, &arr, &capacity, &n))
		return (0);
	close(fd);
	if (!expand_lines_buffer(&arr, &capacity, n))
		return (free_lines_array(arr, n), 0);
	arr[n] = NULL;
	*lines = arr;
	*count = n;
	return (1);
}
