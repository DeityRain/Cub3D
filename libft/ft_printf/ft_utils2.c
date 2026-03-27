/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:15:51 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/07/07 13:18:50 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_fill_ptr_buffer(unsigned long num, char *buffer, int digits)
{
	int	temp;

	temp = digits - 1;
	while (num > 0)
	{
		buffer[temp--] = "0123456789abcdef"[num % 16];
		num /= 16;
	}
}

static int	ft_count_ptr_digits(unsigned long num)
{
	int	digits;

	digits = 0;
	while (num > 0)
	{
		num /= 16;
		digits++;
	}
	return (digits);
}

int	ft_pointer_handler(va_list argsList)
{
	void			*ptr;
	unsigned long	num;
	int				digits;
	char			buffer[17];

	ptr = va_arg(argsList, void *);
	num = (unsigned long)ptr;
	if (num == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	digits = ft_count_ptr_digits(num);
	ft_fill_ptr_buffer(num, buffer, digits);
	write(1, buffer, digits);
	return (digits + 2);
}
