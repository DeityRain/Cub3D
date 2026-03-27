/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 07:49:59 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/07/10 07:50:01 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_char_handler(va_list argsList)
{
	char	c;

	c = (char) va_arg(argsList, int);
	write(1, &c, 1);
	return (1);
}

int	ft_string_handler(va_list argsList)
{
	char	*current;
	int		cpt;

	cpt = 0;
	current = va_arg(argsList, char *);
	if (!current)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*current)
	{
		write(1, current, 1);
		current++;
		cpt++;
	}
	return (cpt);
}

int	ft_decimal_handler(va_list argsList)
{
	int		num;
	char	*str;
	int		i;

	num = va_arg(argsList, int);
	str = ft_itoa(num);
	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	free(str);
	return (i);
}

int	ft_pourcent_handler(void)
{
	write(1, "%", 1);
	return (1);
}
