/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                         :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: obohbot <obohbot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 13:43:07 by obohbot           #+#    #+#             */
/*   Updated: 2026/10/14 12:25:16 by obohbot        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_conv_displ(const char type, va_list frmt)
{
	if (type == 'c')
		return (ft_putchar(va_arg(frmt, int)));
	else if (type == 's')
		return (ft_putstr(va_arg(frmt, char *)));
	else if (type == 'p')
		return (ft_putptr(va_arg(frmt, void *)));
	else if ((type == 'd') || (type == 'i'))
		return (ft_putnbr(va_arg(frmt, int)));
	else if (type == 'u')
		return (ft_putnbr(va_arg(frmt, unsigned int)));
	else if ((type == 'x') || (type == 'X'))
		return (ft_putnbr_hex(va_arg(frmt, unsigned int), type));
	else if (type == '%')
		return (ft_putchar('%'));
	return (-1);
}

int	ft_printf(const char *str, ...)
{
	va_list	frmt;
	int		len;
	int		check;

	va_start(frmt, str);
	len = 0;
	while (*str)
	{
		if (*str == '%')
		{
			check = ft_conv_displ(*(++str), frmt);
			if (check == -1)
				return (-1);
			len += check;
		}
		else
		{
			if (write(1, str, 1) == -1)
				return (va_end(frmt), -1);
			len++;
		}
		str++;
	}
	va_end(frmt);
	return (len);
}
