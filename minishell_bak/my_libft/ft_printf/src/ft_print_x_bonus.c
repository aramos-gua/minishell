/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:36:34 by mtice             #+#    #+#             */
/*   Updated: 2025/02/11 15:33:16 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	find_hexlen(unsigned long x)
{
	int	hexlen;

	hexlen = 0;
	if (x == 0)
		return (1);
	while (x > 0)
	{
		x /= 16;
		hexlen++;
	}
	return (hexlen);
}

int	ft_print_x(unsigned long x, char type)
{
	unsigned long	t;
	char			*base;

	if (type != 'p')
		x = (unsigned int)x;
	t = x;
	if (type == 'x' || type == 'p')
		base = "0123456789abcdef";
	else if (type == 'X')
		base = "0123456789ABCDEF";
	if (t < 16)
		write(1, &base[t], 1);
	else if (t >= 16)
	{
		ft_print_x(t / 16, type);
		write(1, &base[t % 16], 1);
	}
	return (find_hexlen(x));
}

int	ft_print_x_flags(unsigned int x, char type, t_flags s_flags)
{
	int		len;
	char	width;

	len = 0;
	width = ' ';
	if (x == 0)
		s_flags.hash = 0;
	s_flags.plus = 0;
	s_flags.space = 0;
	if (s_flags.precision < 0 && x != 0)
		s_flags.width -= find_hexlen(x);
	if (s_flags.hash == 1 && s_flags.width >= 2)
		s_flags.width -= 2;
	if (s_flags.zero == 1 && s_flags.width > 0)
	{
		len += hps(type, s_flags);
		s_flags.hash = 0;
	}
	len += wpl(type, width, s_flags);
	if (s_flags.precision >= 0 || (s_flags.precision < 0 && x != 0))
		len += ft_print_x(x, type);
	while (s_flags.left_adjust == 1 && s_flags.width-- > 0)
		len += ft_print_c(width);
	return (len);
}
