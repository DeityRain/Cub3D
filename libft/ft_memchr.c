/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:26:12 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/06/16 09:33:29 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr = (const unsigned char *)s;
	unsigned char		target;

	target = (unsigned char)c;
	while (n > 0)
	{
		if (*ptr == target)
			return ((void *)ptr);
		ptr++;
		n--;
	}
	return (NULL);
}
