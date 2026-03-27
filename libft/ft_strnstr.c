/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:10:27 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/06/12 14:03:41 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*little || (big == NULL && !len))
		return ((char *)big);
	while (*(big + i) && i < len)
	{
		j = 0;
		while (*(big + i + j) == *(little + j) && (i + j) < len)
		{
			if (0 == *(little + j + 1))
				return ((char *)big + i);
			++j;
		}
		++i;
	}
	return (NULL);
}
