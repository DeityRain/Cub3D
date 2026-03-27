/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:26:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/07/07 12:26:47 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_conv_handler(char type, va_list argsList)
{
	if (type == 'c')
		return (ft_char_handler(argsList));
	else if (type == 's')
		return (ft_string_handler(argsList));
	else if (type == '%')
		return (ft_pourcent_handler());
	else if (type == 'd' || type == 'i')
		return (ft_decimal_handler(argsList));
	else if (type == 'u')
		return (ft_uint_base10_handler(argsList));
	else if (type == 'x' || type == 'X')
		return (ft_hex_handler(argsList, type));
	else if (type == 'p')
		return (ft_pointer_handler(argsList));
	return (0);
}

int	ft_is_specificator(char c)
{
	return ((c == 'c' || c == 's' || c == '%' || c == 'd' || c == 'i'
			|| c == 'u' || c == 'x' || c == 'X' || c == 'p'));
}

static int	ft_handle_percent(const char **str, va_list argslist)
{
	int	total_printed;

	total_printed = 0;
	if (*((*str) + 1) == '\0')
	{
		write(1, "%", 1);
		total_printed++;
		(*str)++;
		return (-1);
	}
	else if (ft_is_specificator(*((*str) + 1)))
	{
		(*str)++;
		total_printed += ft_conv_handler(**str, argslist);
	}
	else
	{
		write(1, "%", 1);
		total_printed++;
		(*str)++;
		write(1, *str, 1);
		total_printed++;
	}
	return (total_printed);
}

int	ft_printf(const char *str, ...)
{
	va_list	argslist;
	int		total_printed;
	int		percent_result;

	total_printed = 0;
	va_start(argslist, str);
	while (*str)
	{
		if (*str == '%')
		{
			percent_result = ft_handle_percent(&str, argslist);
			if (percent_result == -1)
				break ;
			total_printed += percent_result;
		}
		else
		{
			write(1, str, 1);
			total_printed++;
		}
		str++;
	}
	va_end(argslist);
	return (total_printed);
}
