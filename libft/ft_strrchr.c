/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:06:31 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/06/11 11:09:24 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_found;

	last_found = NULL;
	while (*s)
	{
		if (*s == (char)c)
			last_found = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (last_found);
}
