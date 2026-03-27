/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:14:14 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/07/07 13:22:48 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_fill_uint_buffer(unsigned int num, char *buffer, int digits)
{
	int	temp;

	temp = digits - 1;
	while (num > 0)
	{
		buffer[temp--] = (num % 10) + '0';
		num /= 10;
	}
}

int	ft_uint_base10_handler(va_list argsList)
{
	unsigned int	num;
	unsigned int	temp;
	int				digits;
	char			buffer[11];

	num = va_arg(argsList, unsigned int);
	if (num == 0)
		return (write(1, "0", 1));
	temp = num;
	digits = 0;
	while (temp > 0)
	{
		temp /= 10;
		digits++;
	}
	ft_fill_uint_buffer(num, buffer, digits);
	write(1, buffer, digits);
	return (digits);
}

static void	ft_fill_hex_buffer(unsigned int num, char *buffer, int digits,
		char *hex_digits)
{
	int	temp;

	temp = digits - 1;
	while (num > 0)
	{
		buffer[temp--] = hex_digits[num % 16];
		num /= 16;
	}
}

int	ft_hex_handler(va_list argsList, char format)
{
	unsigned int	num;
	unsigned int	temp;
	int				digits;
	char			buffer[9];
	char			*hex_digits;

	if (format == 'X')
		hex_digits = "0123456789ABCDEF";
	else
		hex_digits = "0123456789abcdef";
	num = va_arg(argsList, unsigned int);
	if (num == 0)
		return (write(1, "0", 1));
	temp = num;
	digits = 0;
	while (temp > 0)
	{
		temp /= 16;
		digits++;
	}
	ft_fill_hex_buffer(num, buffer, digits, hex_digits);
	write(1, buffer, digits);
	return (digits);
}
