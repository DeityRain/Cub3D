/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:31:52 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/06/16 10:02:29 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr_s1;
	const unsigned char	*ptr_s2;

	ptr_s1 = (const unsigned char *)s1;
	ptr_s2 = (const unsigned char *)s2;
	if (n == 0)
	{
		return (0);
	}
	while (n > 0)
	{
		if (*ptr_s1 != *ptr_s2)
		{
			return ((int)*ptr_s1 - (int)*ptr_s2);
		}
		ptr_s1++;
		ptr_s2++;
		n--;
	}
	return (0);
}
