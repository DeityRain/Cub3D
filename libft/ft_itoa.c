/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:44:06 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/06/19 13:03:34 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_len(long long int n)
{
	unsigned int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	len;
	long long int	llnb;

	llnb = n;
	len = ft_len(n);
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (llnb == 0)
	{
		str[0] = '0';
		return (str);
	}
	else if (llnb < 0)
		llnb = -llnb;
	while (len-- > 0)
	{
		str[len] = llnb % 10 + '0';
		llnb /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
