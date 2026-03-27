/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:04:06 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/06/16 11:10:46 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_str;
	int		str_length;

	str_length = ft_strlen(s) + 1;
	new_str = (char *)malloc(str_length);
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, s, str_length);
	return (new_str);
}
