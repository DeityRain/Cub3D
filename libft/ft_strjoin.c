/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:20:58 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/06/18 17:17:20 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_make_str(char const *s1, char const *s2, char *s3)
{
	int	i;

	i = 0;
	while (*s1)
	{
		s3[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		s3[i] = *s2;
		s2++;
		i++;
	}
	s3[i] = '\0';
	return (s3);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		s1_len;
	int		s2_len;
	int		s3_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3_len = s1_len + s2_len;
	s3 = malloc(s3_len + 1);
	if (!s3)
		return (NULL);
	s3 = ft_make_str(s1, s2, s3);
	return (s3);
}
