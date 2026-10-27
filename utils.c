/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                             :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: obohbot <obohbot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 16:48:49 by obohbot           #+#    #+#             */
/*   Updated: 2026/10/16 12:10:03 by obohbot        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putnbr(long n)
{
	int		len;
	int		aux;
	char	num;

	len = 0;
	if (n < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		len += 1;
		n = -n;
	}
	num = n % 10 + '0';
	if (n > 9)
	{
		aux = ft_putnbr(n / 10);
		if (aux == -1)
			return (-1);
		len += aux;
	}
	if (write(1, &num, 1) == -1)
		return (-1);
	len += 1;
	return (len);
}

int	ft_putnbr_hex(unsigned long nbr, char up)
{
	int		len;
	char	*base;
	int		aux;

	len = 0;
	if (up == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (nbr > 15)
	{
		aux = ft_putnbr_hex((nbr / 16), up);
		if (aux == -1)
			return (-1);
		len += aux;
	}
	if (write(1, &base[nbr % 16], 1) == -1)
		return (-1);
	len += 1;
	return (len);
}

int	ft_putptr(void *ptr)
{
	int	len;
	int	aux;

	if (ptr == 0)
	{
		if (ft_putstr("(nil)") == -1)
			return (-1);
		return (5);
	}
	else if (ft_putstr("0x") == -1)
		return (-1);
	len = 2;
	aux = ft_putnbr_hex((unsigned long)ptr, 'x');
	if (aux == -1)
		return (-1);
	len += aux;
	return (len);
}

int	ft_putstr(char *str)
{
	int	len;
	int	i;

	if (!str)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	len = 0;
	i = 0;
	while (str[i])
	{
		if (write(1, &str[i], 1) == -1)
			return (-1);
		len++;
		i++;
	}
	return (len);
}
