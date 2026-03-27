/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:29:10 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/07/16 14:28:31 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);

int	ft_char_handler(va_list argsList);
int	ft_string_handler(va_list argsList);
int	ft_decimal_handler(va_list argsList);
int	ft_pourcent_handler(void);
int	ft_uint_base10_handler(va_list argsList);
int	ft_hex_handler(va_list argsList, char format);
int	ft_pointer_handler(va_list argsList);

int	ft_conv_handler(char type, va_list argsList);
int	ft_is_specificator(char c);

#endif
