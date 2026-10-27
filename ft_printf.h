/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_printf.h                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: obohbot <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/10/14 11:16:06 by obohbot        #+#    #+#                */
/*   Updated: 2026/10/14 13:07:28 by obohbot        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *c, ...);
int	ft_putchar(char c);
int	ft_putnbr(long n);
int	ft_putnbr_hex(unsigned long nbr, char up);
int	ft_putptr(void *ptr);
int	ft_putstr(char *str);

#endif
