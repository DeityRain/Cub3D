/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:23:03 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/06/16 11:44:08 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	size_t			total_size;
	void			*ptr;
	unsigned char	*byte_ptr;
	size_t			i;

	if (num != 0 && size > SIZE_MAX / num)
		return (NULL);
	total_size = num * size;
	if (total_size == 0)
		total_size = 1;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	byte_ptr = (unsigned char *)ptr;
	i = 0;
	while (i < total_size)
	{
		byte_ptr[i] = 0;
		i++;
	}
	return (ptr);
}
