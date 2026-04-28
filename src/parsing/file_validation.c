#include "cub3d.h"

/*Only use file_validation.c for quick checks function*/

static int	check_file_extension(const char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = strlen(filename);
	if (len < 5)
		return (0);
	if (strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

int	validate_file(const char *filename)
{
	int	fd;

	if (!check_file_extension(filename))
	{
		printf("Error: file must have .cub extension\n");
		return (0);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (0);
	}
	close(fd);
	return (1);
}