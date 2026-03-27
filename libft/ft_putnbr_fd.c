/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:09:30 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/06/19 11:05:36 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long int		lln;

	lln = n;
	if (lln < 0)
	{
		ft_putchar_fd('-', fd);
		lln = -lln;
	}
	if (lln >= 10)
		ft_putnbr_fd(lln / 10, fd);
	ft_putchar_fd(lln % 10 + '0', fd);
}
